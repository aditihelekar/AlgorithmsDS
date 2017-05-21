import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.border.Border;

@SuppressWarnings("serial")
public class HomeScreen extends JFrame {

	JPanel m_TopPanel = new JPanel();
    JPanel m_BottomPanel = new JPanel();
    JLabel screenTitle , playerSelectionLabel, gridSizeLabel;
    JCheckBox playerCheckBox, computerCheckBox;
    GridLayout mainTopGrid, mainBottomGrid;
    JComboBox<Integer> comboGridSize;
    Integer[] sizes = new Integer[] {3, 4};
    static String sizeSelected = "3";
    JButton startPlaying;
    Component xcomp;
    String opponentSelected = "Computer";
    String symbolSelected = "X";
    TicTacToeUI m_Tic;
    
    public static int getSizeDim(){
    	return Integer.parseInt(sizeSelected);
    }
    
    public static void main(String[] args) {
        new HomeScreen();
    }
    public void createMainScreen() {
        m_TopPanel.setSize(300, 300);
        m_TopPanel.setBackground(Color.decode("#005b96"));
        m_TopPanel.setAlignmentX(0);
        m_TopPanel.setAlignmentY(0);
        m_TopPanel.setMaximumSize(new Dimension(300,300));
        
        
        mainTopGrid = new GridLayout(7,1); 
        mainTopGrid.setVgap(5);
        m_TopPanel.setLayout(mainTopGrid);
        
        
        //Title
        screenTitle = new JLabel("TicTacToe");
        screenTitle.setFont(new Font("Comic Sans MS", Font.BOLD, 55));
        screenTitle.setForeground(Color.decode("#e6e6fa"));
        screenTitle.setHorizontalAlignment(JLabel.CENTER);
        screenTitle.setVerticalAlignment(JLabel.TOP);
        
        
        
        //Player Selection
        playerSelectionLabel = new JLabel("Select the opponent:");
        playerSelectionLabel.setFont(new Font("Comic Sans MS", Font.BOLD, 30));
        playerSelectionLabel.setForeground(Color.decode("#e6e6fa"));
        playerSelectionLabel.setHorizontalAlignment(JLabel.CENTER);
        playerSelectionLabel.setVerticalAlignment(JLabel.CENTER);
        
        
        
        //Computer
        computerCheckBox = new JCheckBox("Computer", true);
        computerCheckBox.setHorizontalAlignment(JCheckBox.CENTER);
        computerCheckBox.setFont(new Font("Comic Sans MS", Font.BOLD, 20));
        computerCheckBox.setForeground(Color.decode("#e6e6fa"));
        computerCheckBox.setBackground(Color.decode("#005b96"));
        computerCheckBox.addItemListener(new ItemListener() {
        public void itemStateChanged(ItemEvent e) {         
            if(e.getStateChange() == 1)
            {
                playerCheckBox.setSelected(false);
                opponentSelected = "Computer";
            }
         }           
        });
        
      //Player2
        playerCheckBox = new JCheckBox("Player 2", false);
        playerCheckBox.setHorizontalAlignment(JCheckBox.CENTER);
        playerCheckBox.setFont(new Font("Comic Sans MS", Font.BOLD, 20));
        playerCheckBox.setForeground(Color.decode("#e6e6fa"));
        playerCheckBox.setBackground(Color.decode("#005b96"));
        playerCheckBox.addItemListener(new ItemListener() {
        public void itemStateChanged(ItemEvent e) { 
            if(e.getStateChange() == 1)
            {
                computerCheckBox.setSelected(false);
                opponentSelected = "Player";
            }
         }             
        });
        
        gridSizeLabel = new JLabel();
        gridSizeLabel.setFont(new Font("Comic Sans MS", Font.BOLD, 30));
        gridSizeLabel.setForeground(Color.decode("#e6e6fa"));
        gridSizeLabel.setHorizontalAlignment(JLabel.CENTER);
        gridSizeLabel.setVerticalAlignment(JLabel.TOP);
        
        
        comboGridSize = new JComboBox();
        for(int i = 0; i < sizes.length; i++) {
            comboGridSize.addItem(sizes[i]);
        }
        comboGridSize.setSize(1,1);
        comboGridSize.setFont(new Font("Comic Sans MS", Font.BOLD, 35));
        comboGridSize.addActionListener(new ActionListener (){
            public void actionPerformed(ActionEvent event){
                sizeSelected = ((JComboBox)event.getSource()).getSelectedItem().toString();
            }
        });
        
        startPlaying = new JButton("Start Playing");
        startPlaying.setPreferredSize(new Dimension(50,20));
        startPlaying.setFont(new Font("Comic Sans MS", Font.BOLD, 35));
        startPlaying.setForeground(Color.decode("#005b96"));
        startPlaying.setBackground(Color.decode("#FDC944"));
        startPlaying.setBorder(new RoundedBorder(10));
        startPlaying.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
            	//Custom button text
            	Object[] options = {"x","o"};
            	int n = JOptionPane.showOptionDialog(null," Please select your symbol ", "Player 1",JOptionPane.YES_NO_CANCEL_OPTION, JOptionPane.QUESTION_MESSAGE,null,options,options[1]);
            	if(n == 0)
            		symbolSelected = "x";
            	else
            		symbolSelected = "o";
            	m_Tic = new TicTacToeUI(sizeSelected, opponentSelected, symbolSelected);
                setVisible(false);
                
            }
        });
        
        m_TopPanel.add(screenTitle);
        m_TopPanel.add(playerSelectionLabel);
        m_TopPanel.add(computerCheckBox);
        m_TopPanel.add(playerCheckBox);
        m_TopPanel.add(gridSizeLabel);
        m_TopPanel.add(comboGridSize);
        m_TopPanel.add(startPlaying);
        
    }
    
    //Constructor
    public HomeScreen () {
        super("TicTacToe");
        this.setSize(600, 600);
        this.setResizable(true);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        createMainScreen();
        this.add(m_TopPanel);
        this.setVisible(true);
    }
    
    public String getGridSize() {
        return sizeSelected;
    }
    
    public String getOpponent() {
        return opponentSelected;
    }
    
    private class RoundedBorder implements Border {

    private int radius;


    RoundedBorder(int radius) {
        this.radius = radius;
    }


    public Insets getBorderInsets(Component c) {
        return new Insets(this.radius+1, this.radius+1, this.radius+2, this.radius);
    }


    public boolean isBorderOpaque() {
        return true;
    }


    public void paintBorder(Component c, Graphics g, int x, int y, int width, int height) {
        g.drawRoundRect(x, y, width-1, height-1, radius, radius);
    }
}
}

