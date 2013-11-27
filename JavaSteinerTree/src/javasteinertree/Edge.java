/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package javasteinertree;

/**
 *
 * @author elc
 */
public class Edge {

    /* Edge connects start node and end node */
    private final int start;	//start node
    private final int end;		//end node
    private final int weight;
    
    public Edge(int start, int end, int weight) {
        this.start = start;
        this.end = end;
        this.weight = weight;
    }
    
    public int getStart() {
        return this.start;
    }
    public int getEnd() {
        return this.end;
    }
    public int getWeight() {
        return this.weight;
    }
}
