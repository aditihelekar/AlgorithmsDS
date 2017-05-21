import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.SwingUtilities;


public class Game extends JFrame {
	
	Position position = new Position();
	JButton[] buttons = new JButton[position.SIZE];
	int player = 1;	//0 means 2nd player...1 is computer..
	public Game(){
		setLayout(new GridLayout(Position.DIM,Position.DIM));
		for(int i=0;i<Position.SIZE;i++){
			final JButton button = createButton();
			buttons[i] = button;
			final int idx = i;
			button.addMouseListener(new MouseAdapter() {
				@Override
				public void mouseClicked(MouseEvent arg0) {
					if(position.board[idx] == ' '){
						
						if(player == 0){
							//play with another human player
							//button.setText(Character.toString(position.turn));
							//position.move(idx);
							if(!position.isGameEnd()){
								button.setText(Character.toString(position.turn));
								position.move(idx);
							}
							if(position.isGameEnd()){
								String message = position.isWinFor('x')?"X Won!":position.isWinFor('o')?"O won!":"It's a draw.Well played!";						
								JOptionPane.showMessageDialog(null, message);
							}
							
							
						}
						else{
							button.setText(Character.toString(position.turn));
							position.move(idx);
							if(!position.isGameEnd()){
								int best = position.bestMove();
								buttons[best].setText(Character.toString(position.turn));
								position.move(best);
							}
							if(position.isGameEnd()){
								String message = position.isWinFor('x')?"You Won!":position.isWinFor('o')?"Computer won!":"It's a draw.Well played!";
							
								JOptionPane.showMessageDialog(null, message);
							}
						}
						
						
						
						
						
					}
					}
					
			});
		}
		pack();
		setVisible(true);
	}
	
	private JButton createButton() {
		JButton button = new JButton();
		button.setPreferredSize(new Dimension(100,100));
		button.setBackground(Color.GRAY);
		button.setOpaque(true);
		button.setFont(new Font(null, Font.PLAIN, 60));
		add(button);
		return button;
		
	}

	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable(){

			public void run() {
				new Game();			
			}			
		});
	}
}
