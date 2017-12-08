import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;


public class VisualizeGUI {

	private static Scanner sc;

	/**
	 * @param args
	 * @throws Exception 
	 */
	
	
	public static void main(String[] args) throws Exception {
		//args: rows cols array[rows*cols] string
		
		sc = new Scanner(System.in);
		Integer rows;
		Integer cols;
		List<List<Integer>> list = new ArrayList<List<Integer>>();
		int solutionLength;
		String moveSeq = "";
	
		//Getting values from args
		try {
			rows = sc.nextInt();
			cols = sc.nextInt();
			List<Integer> first = new ArrayList<Integer>();
			
			for (int i=0;i<rows*cols;i++) {
				first.add(sc.nextInt());
			}
			list.add(first);
			
			solutionLength = sc.nextInt();
			
			if (solutionLength > 0) moveSeq = sc.next();
			
				
			//Makeing list of moves
			for (int i=0; i<moveSeq.length(); i++) {
				List<Integer> next = new ArrayList<Integer>();
				next = moveFreeTile(rows,cols,list.get(i),moveSeq.charAt(i));
				list.add(next);
			}
		} catch (Exception ex) {
			System.err.println("Bad format of args" + ex.getMessage());
			return;
		}
		
		System.err.println(rows);
		System.err.println(cols);
		for(int i=0;i<list.size();i++) {
			System.err.println(i + ". " + list.get(i));
		}
		System.err.println(solutionLength);
		System.err.println(solutionLength);
		
		Window15 okno = new Window15(rows,cols,list,moveSeq);
		okno.setDefaultCloseOperation(Window15.DISPOSE_ON_CLOSE);
		okno.setVisible(true);

	}
	
	static List<Integer> moveFreeTile(Integer rows, Integer cols, List<Integer> val, char moveDirection) throws Exception
	{
		List<Integer> values = new ArrayList<Integer>(val);
		//Getting position of 0 element
		int zeroPosition = -1;
		for (int i = 0; i < values.size(); i++)
		{
			if (values.get(i) == 0)
			{
				zeroPosition = i;
				break;
			}
		}

		if (zeroPosition == -1) throw new Exception("Board doesn't have 0 element?!");

		if (moveDirection == 'L') {
			//We can't left if 0 element is in first column
			if (zeroPosition%cols == 0) throw new Exception("Illegal Move");
			else {
				Collections.swap(values,zeroPosition, zeroPosition-1);
			}
		}
		else if (moveDirection == 'P') {
			//We can't right if 0 element is in last column
			if ((zeroPosition+1)%cols == 0) throw new Exception("Illegal Move");
			else {
				Collections.swap(values,zeroPosition, zeroPosition +1);
				return values;
			}
		}
		else if (moveDirection == 'G') {
			//We can't up if 0 element is in first row
			if (zeroPosition/cols == 0) throw new Exception("Illegal Move");
			else {
				Collections.swap(values,zeroPosition, zeroPosition - cols);
				return values;
			}
		}
		else if (moveDirection == 'D') {
			//We can't down if 0 element is in last row
			if (zeroPosition / cols == rows-1) throw new Exception("Illegal Move");
			else {
				Collections.swap(values,zeroPosition, zeroPosition + cols);
				return values;
			}
		}
		else throw new Exception("Illegal Move");
		return values;
	}

}
