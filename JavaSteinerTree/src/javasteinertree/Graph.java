/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package javasteinertree;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author elc
 */
public class Graph {
    private final ArrayList<ArrayList<Node>> graph = new ArrayList<>();
    private int edges;
    private final int nodes;
    private boolean[] visitado;
    private List<Edge> lstEdge = new ArrayList<>();
    
    public Graph(int numberOfNodes) {
        this.visitado = new boolean[numberOfNodes];
        this.nodes = numberOfNodes;
        this.edges = 0;
    }
    
    public void addEdge(Edge edge) {
        Node node1 = new Node(edge.getStart(), edge.getWeight());
        if (graph.get(edge.getEnd()) != null) {
            graph.get(edge.getEnd()).add(node1);
        } else {
            graph.add(edge.getEnd(), new ArrayList<Node>());
            graph.get(edge.getEnd()).add(node1);
        }
        Node node2 = new Node(edge.getEnd(), edge.getWeight());
        if (graph.get(edge.getStart()) != null) {
            graph.get(edge.getStart()).add(node2);
        } else {
            graph.add(edge.getStart(), new ArrayList<Node>());
            graph.get(edge.getStart()).add(node2);
        }
        this.lstEdge.add(edge);
    }
    
    public void removeEdge(Edge edge) {
        boolean found = false;
        if (graph.get(edge.getStart()) != null) {
            for (Node node : graph.get(edge.getStart())) {
                if (node.getVertex() == edge.getEnd()) {
                    found = true;
                    graph.get(edge.getStart()).remove(node);
                    break;
                }
            }
        }
        if (found) {
            if (graph.get(edge.getEnd()) != null) {
                for (Node node : graph.get(edge.getEnd())) {
                    if (node.getVertex() == edge.getStart()) {
                        graph.get(edge.getEnd()).remove(node);
                        break;
                    }
                }
            }
            this.edges--;
        }
        this.lstEdge.remove(edge);
    }
    
    public boolean hasLoop(int node) {
        for (int index = 0; index < this.visitado.length; ++index) {
            this.visitado[index] = false;
        }
        for (ArrayList<Node> lstNode : this.graph) {
            for (Node nodeToClean : lstNode) {
                nodeToClean.setAccessed(false);
            }
        }
        
        return hasLoopRecursive(node);
    }
    
    public boolean hasLoopRecursive(int node) {
        this.visitado[node] = true;
        if (this.graph.get(node) != null) {
            for (int indexFirst = 0; indexFirst < this.graph.get(node).size(); ++indexFirst) {
                Node firstNode = this.graph.get(node).get(indexFirst);
                if (firstNode != null && !firstNode.isAccessed()) {
                    firstNode.setAccessed(true);
                    for (int indexSecond = 0; indexSecond < this.graph.get(firstNode.getVertex()).size(); ++indexSecond) {
                        Node secondNode = this.graph.get(firstNode.getVertex()).get(indexSecond);
                        if (secondNode != null && secondNode.getVertex() == node) {
                            secondNode.setAccessed(true);
                            break;
                        }
                    }
                    if (this.visitado[firstNode.getVertex()]) {
                        return true;
                    } else if (hasLoopRecursive(firstNode.getVertex())) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
    
    public Edge getRandomEdge () {
        // Min + (int)(Math.random() * ((Max - Min) + 1))
        int random = (int)(Math.random() * this.edges);
        return this.lstEdge.get(random);
    }
    
    public List<Edge> getEdgeList() {
        return this.lstEdge;
    }
}
