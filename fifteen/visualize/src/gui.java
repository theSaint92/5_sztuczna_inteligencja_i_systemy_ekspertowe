import java.util.ArrayList;
import java.util.List;


public class gui {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		//args: rows cols array[rows*cols] string
		
		Integer rows;
		Integer cols;
		List<List<Integer>> list = new ArrayList<List<Integer>>();
		String moveSeq;
	
		//Getting values from args
		try {
			rows = Integer.parseInt(args[0]);
			cols = Integer.parseInt(args[1]);
			List<Integer> first = new ArrayList<Integer>();
			for (int i=2;i<rows*cols+2;i++) {
				first.add(Integer.parseInt(args[i]));
			}
			list.add(first);
			moveSeq = args[rows*cols+2];
		} catch (Exception ex) {
			System.err.println("Bad format of args");
			return;
		}
		
		System.out.println(rows);
		System.out.println(cols);
		System.out.println(list.get(0));
		System.out.println(moveSeq);
		
		//Makeing list of

		
		
		
		
		Window15 okno = new Window15();
		okno.setDefaultCloseOperation(Window15.DISPOSE_ON_CLOSE);
		okno.setVisible(true);

	}

}
