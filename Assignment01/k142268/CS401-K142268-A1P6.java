package a1p1;
import java.io.*;
import java.util.*;

class Node {
	
	public State location;
	public Node parent;
	public int path_cost;
	
	Node(State state){
		this.location=state;
		this.parent=null;
		this.path_cost=0;
	}
	Node(State state, Node parent){
		this.location= state;
		this.parent=parent;
		this.path_cost = parent.path_cost+1;
		
	}
	public double heuristic(){
		Node goal = new Node(new State(CS401_K142268_A1P6.final_x, CS401_K142268_A1P6.final_y));
    	double g =
    			Math.pow((goal.location.x-this.location.x), 2) + Math.pow((goal.location.y-this.location.y), 2);
    	g = Math.sqrt(g);
    	return g;
    }
}
class State {
	int x;
	int y;
	
	State(int x, int y){
		this.x=x;
		this.y=y;
	}
}
class ANodeComparator implements Comparator<Node>
{
    @Override
    public int compare(Node x, Node y)
    {
        // Assume neither string is null. Real code should
        // probably be more robust
        // You could also just return x.length() - y.length(),
        // which would be more efficient.
    	double f_x = x.heuristic() + x.path_cost;
    	double f_y = y.heuristic() + y.path_cost;
    	if(f_x>f_y)
    		return 1;
    	if(f_x<f_y)
    		return -1;
        return 0;
    }
    
}
public class CS401_K142268_A1P6 {
//	private static final String FILENAME = "D:\\A1-tc1.txt";
//	private static final String FILENAME = "D:\\A1-tc2.txt";
//	private static final String FILENAME = "D:\\A1-tc3.txt";
//	private static final String FILENAME = "D:\\A1-tc4.txt";
//	private static final String FILENAME = "D:\\A1-tc5.txt";
	private static final String FILENAME = "D:\\A1-tc6.txt";

	public static int m, n, init_x, init_y;
	static int final_x, final_y;
	public static void main(String args[]){
		File file = new File(FILENAME);
		try {
	        Scanner sc = new Scanner(file);
	        n = sc.nextInt();
	        m = sc.nextInt();
	        init_x = sc.nextInt();
	        init_y = sc.nextInt();
	        final_x = sc.nextInt();
	        final_y = sc.nextInt();

	        int i =0;
	        int j=0;
	        
	        int [][] maze = new int[n][m];
	        
	        while (sc.hasNext()) {
	        	if(j==m){
	        		j=0;
	        		i++;
	        	}
	            int num = sc.nextInt();
	            maze[i][j] = num;
	            j++;
	        }
	        sc.close();  
	        PrintStream out = new PrintStream(new FileOutputStream("output.txt"));
	        System.setOut(out);
	        boolean pathExistsAStar = AStar(maze);
	        if(!pathExistsAStar){
	        	System.out.println("No solution");
	        }
	      
	    } 
	    catch (FileNotFoundException e) {
	        e.printStackTrace();
	    }	
	}	
	public static boolean AStar(int [][] matrix){
		Comparator<Node> comparator = new ANodeComparator();
        PriorityQueue<Node> queue = 
            new PriorityQueue<Node>(m*n, comparator);
        
        queue.add(new Node(new State(init_x,init_y)));
           
        boolean pathExists = false;
        while(!queue.isEmpty()){
        	Node current = queue.remove();
        	// System.out.println("State: ("+current.location.x+","+current.location.y+") "+current.heuristic());
             
        	if(current.location.x==final_x && current.location.y==final_y && matrix[current.location.x][current.location.y]==0){
        		pathExists = true;
        		if(pathExists){
        			printPath(current);
                }
        		break;
        	}
        	matrix[current.location.x][current.location.y]=1;
        	List<Node> neighbours = getNeighbours(queue, matrix, current);
        	queue.addAll(neighbours);
        }
        return pathExists;
	}
	public static boolean greedyFirst(int [][] matrix){
		Comparator<Node> comparator = new ANodeComparator();
        PriorityQueue<Node> queue = 
            new PriorityQueue<Node>(m*n, comparator);
        
        queue.add(new Node(new State(init_x,init_y)));
           
        boolean pathExists = false;
        while(!queue.isEmpty()){
        	Node current = queue.remove();
        	if(current.location.x==final_x && current.location.y==final_y && matrix[current.location.x][current.location.y]==0){
        		pathExists = true;
        		if(pathExists){
        			printPath(current);
                }
        		break;
        	}
        	matrix[current.location.x][current.location.y]=1;
        	List<Node> neighbours = getNeighbours(queue, matrix, current);
        	queue.addAll(neighbours);
        }
        return pathExists;
	}
	
	public static List<Node> getNeighbours(PriorityQueue<Node> my_list, int[][]matrix, Node node){
    	List<Node> children = new ArrayList<Node>();
    	//Up
        if(isValidPoint(matrix, node.location.x-1, node.location.y)) {
        	if(!isPresent(my_list, node.location.x-1, node.location.y)){
        	children.add(new Node(new State(node.location.x-1, node.location.y),node));
        	}
        }
        //Down
        if(isValidPoint(matrix, node.location.x+1, node.location.y)) {
        	if(!isPresent(my_list,node.location.x+1, node.location.y)){
            children.add(new Node(new State(node.location.x+1, node.location.y),node));
        	}
        }
        //Right
        if(isValidPoint(matrix, node.location.x, node.location.y+1)) {
        	if(!isPresent(my_list, node.location.x, node.location.y+1)){
            children.add(new Node(new State(node.location.x, node.location.y+1),node));
        	}
        }
        //Left
        if(isValidPoint(matrix, node.location.x, node.location.y-1)) {
        	if(!isPresent(my_list, node.location.x, node.location.y-1)){
            children.add(new Node(new State(node.location.x, node.location.y-1),node));
        	}
        }
        //LeftUp
        if(isValidPoint(matrix, node.location.x-1, node.location.y - 1)) {
        	if(!isPresent(my_list, node.location.x-1, node.location.y - 1)){
            children.add(new Node(new State(node.location.x-1, node.location.y - 1),node));
        	}
        }
        //LeftDown
        if(isValidPoint(matrix, node.location.x+1, node.location.y - 1)) {
        	if(!isPresent(my_list,node.location.x+1, node.location.y - 1)){
            children.add(new Node(new State(node.location.x+1, node.location.y - 1),node));
        	}
        }
        //RightUp
        if(isValidPoint(matrix, node.location.x-1, node.location.y +1)) {
        	if(!isPresent(my_list,node.location.x-1, node.location.y +1)){
            children.add(new Node(new State(node.location.x-1, node.location.y +1),node));
  //          child_count++;
        	}
        }
        //RightDown
        if(isValidPoint(matrix, node.location.x+1, node.location.y + 1)) {
        	if(!isPresent(my_list, node.location.x+1, node.location.y + 1)){
            children.add(new Node(new State(node.location.x+1, node.location.y + 1),node));
        	}
        }
        return children;
    }
    public static boolean isPresent(PriorityQueue<Node> my_list, int a, int b){
    	int size = my_list.size();
    	for(Node iter : my_list){
    		if(iter.location.x==a && iter.location.y==b){
    			return true;
    		}
    	}
    	return false;
    }
	public static void printPath(Node current){
		List<Node> path = new ArrayList<Node>();
		while(current!=null){
			path.add(current);
			current=current.parent;
		}
		int total_cost = path.size();
		while(path.size()>0){
			Node step = path.remove(path.size()-1);
			System.out.println(step.location.x+" "+step.location.y);
		}
		System.out.println(total_cost);
	}
	
    public static boolean isValidPoint(int[][] matrix, int x, int y) {
        return !(x < 0 || x >= n || y < 0 || y >= m) && (matrix[x][y] != 1);
    }
}