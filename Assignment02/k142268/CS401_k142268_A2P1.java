/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package CS401_k142268_A2P1;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Node {
    public Node parent;
    int depth;
    public int eval_cost;
    public int [][] board= new int[4][6];
    //Initial node has no parent
    Node(int[][] input){
        this.parent=null;
        this.board=input;
        this.eval_cost=0;
        this.depth = 0;
    }
    //Other nodes have parent
    Node(Node parent, int[][] input){
	this.board=input;
        this.parent=parent;
        this.eval_cost=0;
        this.depth = parent.depth + 1;
    }
}

/**
 *
 * @author Sadiq
 */

public class CS401_k142268_A2P1 {
    //Can also use this path for test-cases:  \\k142268\\test_cases
    private static final String FILENAME = "D:\\a2-tc1.txt";
  //  private static final String FILENAME = "D:\\a2-tc2.txt";
  //  private static final String FILENAME = "D:\\a2-tc3.txt";
//    private static final String FILENAME = "D:\\a2-tc4.txt";
    
    public static final int COLUMN=6, ROW=4, cutOffDepth = 2;
    
    public static void main(String[] args) {
        // TODO code application logic here
        File file = new File(FILENAME);
	try{
            Scanner sc = new Scanner(file);
            int i =0;
            int j=0;

            int [][] board = new int[ROW][COLUMN];

            while (sc.hasNext()) {
                    if(j==COLUMN){
                            j=0;
                            i++;
                    }
                int num = sc.nextInt();
                board[i][j] = num;
                j++;
            }
            sc.close();
            //1 means MIN player, 2 means MAX player
            //First ply
            int player = whoseTurn(board);
            List<Node> possible_moves = cutoff_function(board, player);
            
            //Second ply
            System.out.println("------------------------GOING INTO PLY 2------------------------------"); 
            int nextPlayer=0;
            if(player==1)
                nextPlayer=2;
            else if(player==2)
                nextPlayer=1;
            player=nextPlayer;
            for(int iter=0;iter<possible_moves.size();iter++){
                    System.out.println("--------------------------CHILD "+ iter+ "'s children----------------------------");                
                List<Node> new_moves = cutoff_function((possible_moves.get(iter)).board,player);
            }
            
        }
	catch (FileNotFoundException e) {
	        e.printStackTrace();
        }
    }
    
    //Whose turn is it? Based on the number of red and white pieces
    public static int whoseTurn(int[][] board){
        int[] oneBoard = twoToOne(board);
        int countOne =0;
        int countTwo =0;
        for(int i=0; i<ROW*COLUMN; i++){
            if(oneBoard[i]==1){
                countOne++;
            }
            else if(oneBoard[i]==2){
                countTwo++;
            }
        }
        if(countOne>countTwo)
            return 2;
        else if(countOne<countTwo)
            return 1;
        else
            //neutral board, hardcode player=computer
            return 1;
            
    }
    
    //Generates and evaluates children
    public static List<Node> cutoff_function(int[][] parent, int player){
        Node parent_node = new Node(parent);
        List<Node> frontier =new ArrayList<Node>();
        List<Node> neighbours =getChildren(parent_node, player);
        frontier.addAll(neighbours);
        int nextPlayer = 0;
        if(player==1)
            nextPlayer=2;
        else if(player==2)
            nextPlayer=1;
        for(int i=0;i<frontier.size();i++){
            cutOffValue(frontier.get(i), nextPlayer);
        }
        return frontier;
    }

    //Gives points to a child (Actual Evaluation takes place here)
    public static int cutOffValue(Node current, int nextTurn){
        /*
        New algo:
        - Make the 24 subsets possible. How?
        Make 6 columns, 6 diagonals (3 pos and 3 neg) - hard code, 12 from rows (3 from each)
        - Evaluate each. How?
        all 0's: reject.
        mix of 1 and 2: reject.
        just 2's: points = number of 2's multiply by 2. 
        just 1's: points = number of 1's. 
        - Return sum of all evaluation
        */
        int v_score = makeVerticalSubsets(current.board);
        int h_score = makeHorizontalSubsets(current.board);
        int d_score = makeDiagonalSubsets(current.board);
        
        printBoard(current.board);
//      System.out.println("Child depth: "+ current.depth);
        int sum_score = v_score + h_score + d_score;
        //The player who has the next turn has an advantage so
        /*
        if(nextTurn==2)
            sum_score++;
        else if(nextTurn==1)
            sum_score--;
        */
        System.out.println("Evaluation cost: "+sum_score);
        current.eval_cost=sum_score;
        return sum_score;
    }
    
    //Make and evaluate
    public static int makeVerticalSubsets(int[][] board){
        int[] one_board = new int[24];
        one_board = twoToOne(board);
        List<List> papa_list = new ArrayList<List>();
        for(int i=0;i<COLUMN;i++){
            List<Integer> beta_list= new ArrayList<Integer>();
            papa_list.add(beta_list);
        }
        for(int j=0;j<24;j++){
            //bin for COLUMN 0
            if(j%6==0){
                List<Integer> new_temp = papa_list.get(0);
                new_temp.add(one_board[j]);
            }
            //bin for COLUMN 1
            if(j%6==1){
                List<Integer> new_temp = papa_list.get(1);
                new_temp.add(one_board[j]);
            }
            //bin for COLUMN 2
            if(j%6==2){
                List<Integer> new_temp = papa_list.get(2);
                new_temp.add(one_board[j]);
            }
            //bin for COLUMN 3
            if(j%6==3){
                List<Integer> new_temp = papa_list.get(3);
                new_temp.add(one_board[j]);
            }
            //bin for COLUMN 4
            if(j%6==4){
                List<Integer> new_temp = papa_list.get(4);
                new_temp.add(one_board[j]);
            }
            //bin for COLUMN 5
            if(j%6==5){
                List<Integer> new_temp = papa_list.get(5);
                new_temp.add(one_board[j]);
            }
        }
        
        papa_list = calculateCost(papa_list);
        int v_score = 0;
        for(int i=0;i<papa_list.size();i++){
            List<Integer> temp = papa_list.get(i);
            v_score+=temp.get(4);
        }
        return v_score;
    }

    public static int makeHorizontalSubsets(int[][] board){
        int[] one_board = new int[24];
        one_board = twoToOne(board);
        List<List> papa_list = new ArrayList<List>();
        for(int i=0;i<3*ROW;i++){
        List<Integer> beta_list= new ArrayList<Integer>();
        papa_list.add(beta_list);
        }
        int index_count=0;
        for(int i=0;i<ROW;i++){
            for(int j=0; j<3; j++){
                List<Integer> new_temp = papa_list.get(index_count);
                for(int k=j;k<j+4;k++){
                new_temp.add(board[i][k]);
                }
                index_count++;
            }
        }
        papa_list = calculateCost(papa_list);
        int h_score = 0;
        for(int i=0;i<papa_list.size();i++){
            List<Integer> temp = papa_list.get(i);
            h_score+=temp.get(4);
        }
        return h_score;
    }

    public static int makeDiagonalSubsets(int[][] board){
        int[] one_board = new int[24];
        one_board = twoToOne(board);
        List<List> papa_list = new ArrayList<List>();
        for(int i=0;i<6;i++){
        List<Integer> beta_list= new ArrayList<Integer>();
        papa_list.add(beta_list);
        }
        int index_count=0;
        for(int i=0;i<2;i++){
            if(i==0){
                for(int j=0; j<3; j++){
                    List<Integer> new_temp = papa_list.get(index_count);
                    for(int k=j;k<j+22;k+=7){
                    new_temp.add(one_board[k]);
                    }
                    index_count++;
                }                    
            }
            if(i==1){
                for(int j=0; j<3; j++){
                    List<Integer> new_temp = papa_list.get(index_count);
                    for(int k=3+j;k<j+22;k+=5){
                    new_temp.add(one_board[k]);
                    }
                    index_count++;
                }                    
            }
        }
        papa_list = calculateCost(papa_list);
        int d_score = 0;
        for(int i=0;i<papa_list.size();i++){
            List<Integer> temp = papa_list.get(i);
            d_score+=temp.get(4);
        }
        return d_score;

    }
    
    //Gives points to each subset of 4.
    public static List<List> calculateCost(List<List> papa_list){
        /*
        algo for evaluation:
        if contains 2 
            yes - check if also contains 1
                yes - drop it, continue
                no - count # of 2's, add points twice, continue
            no - check if contains 1
                yes - count # of 1's, subtract points, continue
                no - line of 0's -  drop it
        */

        int points = 0;
        int count =0;
        for(int i=0;i<papa_list.size();i++){
            points = 0;
            List<Integer> temp = papa_list.get(i);
            if(temp.contains(2)){
                if(temp.contains(1)){
                    temp.add(points);
                }
                else{
                    count =0; 
                    for(int num : temp){
                        if(num==2){
                            count++;
                        }
                    }
                    points+=count;
                    //playing offensive game: you get more points for attacking (playing to win) rather than defensing (cancelling out opponent's move) 
                    //temp.add(2*points);
                    temp.add(points);
                }
            }
            else if(temp.contains(1)){
                count =0; 
                    for(int num : temp){
                        if(num==1){
                            count--;
                        }
                    }
                    points+=count;
                    temp.add(points);
            }
            else{
                temp.add(points);
            }
        }
       return papa_list; 
    }
        
    //converts a 2D matrix into a 1D matrix
    public static int[] twoToOne(int[][] two_board){
        int[] one_board = new int[24];
        int i=0;
        for(int row=0; row<ROW; row++){
            for(int column = 0; column < COLUMN; column++){
                one_board[i] = two_board[row][column];
                i++;
            }
        }
        return one_board;
    }

    //generates the children (6) of a node column by column i.e. from column 0 to column 5
    public static List<Node> getChildren(Node parent, int player){
        //System.out.println("Parent Board: ");
        //printBoard(parent.board);
    	List<Node> children = new ArrayList<Node>();
        int[][] parent_matrix = parent.board;
        int[][] copy_matrix = new int[ROW][COLUMN];
        //deep copy
        for(int i=0;i<ROW;i++){
            for(int j=0;j<COLUMN;j++){
                copy_matrix[i][j]=parent_matrix[i][j];
            }
        }
        
        int[][] child_matrix = new int[ROW][COLUMN];
        int column = 0;
        for(column=0; column< COLUMN; column++){
            //if a column is already full, then no need to generate it as a child.
            if(isValid(parent_matrix, column)){
                child_matrix = generateChildMatrix(copy_matrix, column, player);
                Node child_node = new Node(parent, child_matrix);
                children.add(child_node);
            }
        }
        int counter =1;        
        for(Node child : children){
            //System.out.println("Child: "+counter++);
            //printBoard(child.board);
        }
        return children;
    }
    //Gets a matrix with a column to put the disk in. Decides by checking which row is empty from row 3 to row 0
    public static int[][] generateChildMatrix(int[][] parent_matrix, int column, int player){
        int[][] child_copy = new int[ROW][COLUMN];
        //deep copy
        for(int i=0;i<ROW;i++){
            for(int j=0;j<COLUMN;j++){
                child_copy[i][j]=parent_matrix[i][j];
            }
        }
        for(int i=3; i>=0; i--){
            if(child_copy[i][column]==0){
                child_copy[i][column]=player;
                break;
           }
        }
        return child_copy;
    }

    //checks if any row is empty within a given column of a matrix
    public static boolean isValid(int[][] matrix, int column) {
        return (matrix[0][column]==0 || matrix[1][column]==0 || matrix[2][column]==0 || matrix[3][column]==0);
    }
    
    //prints the Matrix
    public static void printBoard(int[][] board){
        for(int i=0;i<ROW;i++){
            for(int j=0;j<COLUMN;j++){
                System.out.print(board[i][j]+" ");
            }
            System.out.println();
        }          
    }

}
