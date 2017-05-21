
import java.awt.Color;


import java.awt.Dimension;
import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JOptionPane;


@SuppressWarnings("serial")
public class TicTacToeUI extends JFrame {
    int buttonSize = 0;
        int buttonPos = 0;
        int gridSize = 0;
        ImageIcon m_X, m_O;
        Position position;
        int player = 0;//0 means 2nd player...1 is computer..
        AudioPlayer m_Player;
        String m_Symbol;
        
    public TicTacToeUI(String size, String opponent, String symbol) {
        super("TicTacToe");
        JPanel m_Panel = new JPanel();
        int nxn = 3;
        gridSize = nxn;
        position  = new Position();
        nxn = Integer.parseInt(size);
        System.out.println("nxn " + nxn);
        if(opponent == "Player")
        	player = 0;	
        else
        	player = 1;
        
        setSize(600,600);
        setResizable(true);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        if(nxn == 3)
            buttonSize = 150;
        else if(nxn == 5)
            buttonSize = 100;
        else
            buttonSize = 70;
        
        m_Symbol = symbol;
        System.out.println(m_Symbol.charAt(0));
        position.setTurn(m_Symbol.charAt(0));
        //////////////////////////////// Resources////////////////////////////
        m_O = new ImageIcon(new ImageIcon(this.getClass().getResource("/o.png")).getImage().getScaledInstance(buttonSize, buttonSize, Image.SCALE_DEFAULT));
        m_X = new ImageIcon(new ImageIcon(this.getClass().getResource("/x.png")).getImage().getScaledInstance(buttonSize, buttonSize, Image.SCALE_DEFAULT));
        
        m_Player = new AudioPlayer();
        //////////////////////////////////////////////////////////////////////
        
        
        
        final JButton[] m_Buttons = new JButton[nxn * nxn];
        m_Panel.setLayout(new GridLayout(nxn,nxn));
        for(int i = 0; i < (nxn*nxn); i++){
            final int index = i;
            final JButton m_Button = new JButton();
            m_Buttons[i] = m_Button;
            buttonPos = i;
            m_Button.setBorder(BorderFactory.createMatteBorder(5,5,5,5, Color.decode("#FDC944")));
            m_Button.setPreferredSize(new Dimension(100,100));
            m_Button.setBackground(Color.decode("#FDC944"));
            m_Button.setOpaque(false);
            m_Button.addMouseListener(new MouseListener() {
                public void mouseClicked(MouseEvent e) {
                	m_Player.playAudio();
                	if(player == 0){
						//play with another human player
						//button.setText(Character.toString(position.turn));
						//position.move(idx);
						if(!position.isGameEnd()){
							if(position.turn == 'x') {
		                        m_Button.setIcon(m_X);
		                    }
		                    else {
		                        m_Button.setIcon(m_O);
		                    }
							position.move(index);
						}
						if(position.isGameEnd()){
							String message = position.isWinFor('x')?"X Won!":position.isWinFor('o')?"O won!":"It's a draw.Well played!";						
							int dialogButton = JOptionPane.OK_OPTION;
	                        JOptionPane.showMessageDialog(null, message);
	                        if(dialogButton == JOptionPane.YES_OPTION) {
	                            System.exit(0);
	                        }
						}
					}
                	else
                	{
	                    if(position.turn == 'x') {
	                        m_Button.setIcon(m_X);
	                    }
	                    else {
	                        m_Button.setIcon(m_O);
	                    }
	                    position = position.move(index);
	                    if(!position.isGameEnd()) {
	                    	
	                        int best = position.bestMove();
	                        if(position.turn == 'x') {
	                            m_Buttons[best].setIcon(m_X);
	                        }
	                        else {
	                            m_Buttons[best].setIcon(m_O);
	                        }
	                        position = position.move(best);
	                    }
	                    if(position.isGameEnd()) {
	                        String message = position.isWinFor('x')?"X Won!":position.isWinFor('o')?"O won!":"It's a draw.Well played!";
	                        int dialogButton = JOptionPane.OK_OPTION;
	                        JOptionPane.showMessageDialog(null, message);
	                        if(dialogButton == JOptionPane.YES_OPTION) {
	                            System.exit(0);
	                        }
	                    }
                	}
                }

                public void mousePressed(MouseEvent e) {}

                public void mouseReleased(MouseEvent e) {}

                public void mouseEntered(MouseEvent e) {}

                public void mouseExited(MouseEvent e) {}
            });
            m_Panel.add(m_Button);
        }
        add(m_Panel);
        
        setVisible(true);
    }
    
    protected void move(int idx) {
        
    }
    
}