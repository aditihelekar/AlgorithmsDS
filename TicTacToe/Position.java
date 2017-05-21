
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class Position {
	public char[] board;
	public char turn;
	//public int gridSize;
	public static int DIM = getDim();
	public static final int SIZE = DIM * DIM;
	private Map<Integer, Integer> cache = new HashMap<Integer, Integer>();
	
	public Position(){
		turn = 'x';
		board = new char[SIZE];
		for(int i=0;i<SIZE;i++){
			board[i] = ' ';
		}
	}


	public static int getDim() {
		return HomeScreen.getSizeDim()== 3 ? 3: 4;
	}


	public Position(String string,char turn) {
		this.board = string.toCharArray();
		this.turn = turn;
	}


	public Position move(int index) {
		board[index] = turn;
		turn = turn == 'x'? 'o' : 'x';
		return this;
	}


	public Position unmove(int i) {
		board[i] = ' ';
		turn = turn == 'x' ? 'o' : 'x';
		return this;
	}
	
	public String toString(){
		return new String(board);
	}


	public List<Integer> possibleMoves() {
		List<Integer> list = new ArrayList<Integer>();
		for(int i=0;i< board.length;i++){
			if(board[i] == ' '){
				list.add(i);
			}
			
		}
		return list;
	}


	public boolean isWinFor(char turn) {
		boolean isWin = false;
		for(int i=0;i<SIZE;i+=DIM){
			isWin = isWin || lineMatch(turn,i,i+DIM,1);
		}
		for(int i=0;i<DIM;i++){
			isWin = isWin || lineMatch(turn,i,SIZE,DIM);
		}
		isWin = isWin || lineMatch(turn, 0, SIZE, DIM+1);
		isWin = isWin || lineMatch(turn, DIM-1, SIZE-1, DIM-1);
			
		return isWin;
	}


	private boolean lineMatch(char turn, int start, int end, int step) {
		for(int i=start;i<end;i+=step){
			if(board[i]!= turn){
				return false;
			}
		}
		return true;
	}

	public int code(){
		int value = 0;
		for(int i=0;i<SIZE;i++){
			value = value*3;
			if(board[i] == 'x'){
				value+=1;
			}
			else if(board[i] == 'o'){
				value+=2;
			
			}
		}
		return value;
	}

	public int miniMax() {
		Integer key = code();
		Integer value = cache.get(key);
		if(value!=null) return value;
		if(isWinFor('x')) return blanks()+1;
		if(isWinFor('o')) return -blanks()-1;
		if(blanks() == 0) return 0;
		List<Integer> list = new ArrayList<Integer>();
		for (Integer idx : possibleMoves()) {
			list.add(move(idx).miniMax());
			unmove(idx);
			
		}
		value = turn =='x' ? Collections.max(list) : Collections.min(list);
		cache.put(key, value);
		return value;
	}


	public int blanks() {
		int total = 0;
		for(int i=0;i<SIZE;i++){
			if(board[i]==' '){
				total++;
			}
		}
		return total;
	}


	public int bestMove() {
		
		Comparator<Integer> cmp = new Comparator<Integer>() {

			public int compare(Integer first, Integer second) {
				int a = move(first).miniMax();
				unmove(first);
				int b = move(second).miniMax();
				unmove(second);
				return a-b;
			}
		};
		List<Integer> list =  possibleMoves();
		return turn == 'x' ? Collections.max(list,cmp) : Collections.min(list,cmp);
	
	}


	public boolean isGameEnd() {
		// TODO Auto-generated method stub
		return isWinFor('x') || isWinFor('o') || blanks()==0;
	}
	
	public void setTurn(char turnp){
		turn = turnp == 'x' ? 'x' : 'o';
	}
}
