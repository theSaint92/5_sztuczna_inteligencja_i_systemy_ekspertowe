import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

import java.awt.Font;
import java.util.Hashtable;
import java.util.List;


public class Window15 extends JFrame implements ChangeListener {

	private static final long serialVersionUID = 1L;
	
	private List<List<Integer>> list;
	private int rows;
	private int cols;
	
	private static int BOUND=10;
	private static int DISTANCE=4; //Between Tiles
	private static int TILE_SIZE=80;
	private static int SLIDER_HEIGHT=50;
	private static int COUNTER_HEIGHT=20;
	private static int INFO_HEIGHT = 80;
	private static int MINIMUM_WIDTH = 200; //I't looks ugly if smaller - basicly only used in 1 column puzzle case	
	
	private JButton[] puzzle;
	private JSlider slider;
	private JLabel counter;
	private JLabel info;
	private JLabel extraordinaryState;
	
	public Window15(Integer rows, Integer cols, List<List<Integer>> list, String moveSeq, String testInfo) {
		this.list = list;
		this.rows = rows;
		this.cols = cols;
		
		int windowWidth = 2*BOUND + cols*TILE_SIZE + cols*DISTANCE+14;
		int windowHeight = 2*BOUND + rows*TILE_SIZE + rows*DISTANCE + SLIDER_HEIGHT + 50 + COUNTER_HEIGHT + INFO_HEIGHT;
		
		if (windowWidth < MINIMUM_WIDTH) windowWidth = MINIMUM_WIDTH;
		setSize(windowWidth, windowHeight);
		setTitle("Solving " + rows + "x" + cols + " puzzle");
		setLayout(null);
		Integer size = rows*cols;
		
		puzzle = new JButton[size];
		
		//initialize puzzle with 0 state
		for (int i=0; i<size ; i++) {
			puzzle[i] = new JButton(Integer.toString(list.get(0).get(i)));
			Integer currentRow = i/cols;
			Integer currentCol = i%cols;
			puzzle[i].setBounds(BOUND + currentCol*(DISTANCE+TILE_SIZE), BOUND + currentRow*(DISTANCE+TILE_SIZE), TILE_SIZE, TILE_SIZE);
			puzzle[i].setFont(new Font("Arial", Font.BOLD, 40));
			puzzle[i].setEnabled(false);
			add(puzzle[i]);
			if(puzzle[i].getText().equals("0")) puzzle[i].setVisible(false);
			puzzle[i].setEnabled(false);
		}
		
		if (list.size() > 1) {
			slider = new JSlider(JSlider.HORIZONTAL, 0, list.size()-1, 0);
		    slider.setBounds(BOUND-3, 2*BOUND+rows*TILE_SIZE+rows*DISTANCE, windowWidth-2*BOUND, SLIDER_HEIGHT);
		    add(slider);
		    //Turn on labels at major tick marks.
		    slider.setMajorTickSpacing(list.size());
		    slider.setMinorTickSpacing(list.size()/10);
		    slider.setPaintTicks(true);
		    slider.setPaintLabels(true);
		    //Create the label table
		    Hashtable<Integer, JLabel> labelTable = new Hashtable<Integer, JLabel>();
		    labelTable.put( new Integer( 0 ), new JLabel("Start State") );
		    labelTable.put( new Integer( list.size()-1 ), new JLabel("Solved") );
		    slider.setLabelTable( labelTable );
			
		    slider.addChangeListener(this);
		    
			//Add text field for repoName
			String text1 = "0/" + (list.size()-1);
			counter = new JLabel(text1);
			//counter.setFont(new Font("Arial", Font.PLAIN, 20));
			counter.setHorizontalAlignment(JLabel.CENTER);
			counter.setBounds(BOUND, 2*BOUND+rows*TILE_SIZE+rows*DISTANCE + SLIDER_HEIGHT, windowWidth-2*BOUND, COUNTER_HEIGHT);
			add(counter);
		}
		else {
			//Add text field for repoName
			String text1 = "NO MOVES";
			extraordinaryState = new JLabel(text1);
			//counter.setFont(new Font("Arial", Font.PLAIN, 20));
			extraordinaryState.setHorizontalAlignment(JLabel.CENTER);
			extraordinaryState.setBounds(BOUND, 2*BOUND+rows*TILE_SIZE+rows*DISTANCE, windowWidth-2*BOUND, COUNTER_HEIGHT + SLIDER_HEIGHT);
			add(extraordinaryState);
		}

		
		info = new JLabel(testInfo);
		info.setBounds(BOUND, 2*BOUND+rows*TILE_SIZE+rows*DISTANCE + SLIDER_HEIGHT + COUNTER_HEIGHT, windowWidth-2*BOUND, INFO_HEIGHT);
		add(info);
		
		
	}
	
	public void stateChanged(ChangeEvent e) {
	    JSlider source = (JSlider)e.getSource();
	    if (!source.getValueIsAdjusting()) {
	        int state = (int)source.getValue();
	        counter.setText(state + "/" + (list.size()-1));
	  
			for (int i=0; i<rows*cols ; i++) {
				puzzle[i].setText(Integer.toString(list.get(state).get(i)));
				if(puzzle[i].getText().equals("0")) puzzle[i].setVisible(false);
				else puzzle[i].setVisible(true);
			}
	        
	    }
	}
	
}
