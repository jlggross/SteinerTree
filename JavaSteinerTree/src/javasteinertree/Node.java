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
public class Node {
    private final int vertex;
    private final int weight;
    private boolean accessed = false;
    
    public Node(int vertex, int weight) {
        this.vertex = vertex;
        this.weight = weight;
    }
    
    public int getVertex() {
        return this.vertex;
    }
    
    public int getWeight() {
        return this.weight;
    }
    
    public boolean isAccessed() {
        return this.accessed;
    }
    
    public void setAccessed(boolean value) {
        this.accessed = value;
    }
}
