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
public class Solution extends Graph {
    private final List<Integer> lstTerminal = new ArrayList<>();
    private final List<Integer> lstSolutionNode = new ArrayList<>();
    private int evaluation;
    private int tabuCounter;
    
    public Solution(int numberOfNodes) {
        super(numberOfNodes);
    }
    
    public Solution(Solution solution) {
        super(solution.getNumberOfNodes());
        for (ArrayList<Node> lstNode : solution.getGraph()) {
            ArrayList<Node> newLstNode = new ArrayList<>();
            newLstNode.addAll(lstNode);
            this.graph.add(newLstNode);
        }
        this.evaluation = solution.getEvaluation();
        this.tabuCounter = solution.getTabuCounter();
        this.lstEdge.addAll(solution.getEdgeList());
        this.lstTerminal.addAll(solution.getTerminalList());
        this.lstSolutionNode.addAll(solution.getSolutionNodeList());
    }
    
    public List<Integer> getTerminalList() {
        return this.lstTerminal;
    }
    
    public void insertTerminal(int terminal) {
        this.lstTerminal.add(terminal);
    }
    
    public int getEvaluation() {
        return this.evaluation;
    }
    
    public void setEvaluation(int evaluation) {
        this.evaluation = evaluation;
    }
    
    // TODO talvez não seja possivel dar override
    @Override
    public void addEdge(Edge edge) {
        boolean foundEdge = false;
        for (int index = 0; index < this.graph.get(edge.getEnd()).size(); index++) {
            if (this.graph.get(edge.getEnd()).get(index).getVertex() == edge.getStart()) {
                foundEdge = true;
                break;
            }
        }
        if (!foundEdge) {
            Node newNodeStart = new Node(edge.getWeight(), edge.getStart());
            this.graph.get(edge.getStart()).add(newNodeStart);
            Node newNodeEnd = new Node(edge.getWeight(), edge.getEnd());
            this.graph.get(edge.getEnd()).add(newNodeEnd);
            this.edges++;
            this.lstEdge.add(edge);
            this.evaluation = edge.getWeight();
        }
        boolean foundStart = false;
        boolean foundEnd = false;
        for (int index = 0; index < this.lstSolutionNode.size(); index++) {
            if (this.lstSolutionNode.get(index).doubleValue() == edge.getStart()) {
                foundStart = true;
            } else if (this.lstSolutionNode.get(index).doubleValue() == edge.getEnd()) {
                foundEnd = true;
            }
            if (foundStart && foundEnd) {
                break;
            }
        }
        if (foundStart) {
            this.lstSolutionNode.add(edge.getStart());
        }
        if (foundEnd) {
            this.lstSolutionNode.add(edge.getEnd());
        }
    }
    
    // TODO talvez não seja possivel dar override
    @Override
    public void removeEdge(Edge edge) {
        boolean found = false;
        for (int index = 0; index < this.graph.get(edge.getStart()).size(); index++) {
            if (this.graph.get(edge.getStart()).get(index).getVertex() == edge.getEnd()) {
                this.evaluation -= this.graph.get(edge.getStart()).get(index).getWeight();
                found = true;
                this.graph.get(edge.getStart()).remove(index);
                this.lstEdge.remove(edge);
                break;
            }
        }
        if (found) {
            for (int index = 0; index < this.graph.get(edge.getEnd()).size(); index++) {
                if (this.graph.get(edge.getEnd()).get(index).getVertex() == edge.getStart()) {
                    this.graph.get(edge.getEnd()).remove(index);
                    break;
                }
            }
            this.edges--;
        }
        // TODO para remover os itens sem dar problema, o for foi invertido, verifique se está tudo ok
        if (this.graph.get(edge.getStart()).isEmpty()) {
            for (int index = this.lstSolutionNode.size()-1; index >= 0; index--) {
                if (this.lstSolutionNode.get(index) == edge.getStart()) {
                    this.lstSolutionNode.remove(index);
                }
            }
        }
        // TODO para remover os itens sem dar problema, o for foi invertido, verifique se está tudo ok
        if (this.graph.get(edge.getEnd()).isEmpty()) {
            for (int index = this.lstSolutionNode.size()-1; index >= 0; index--) {
                if (this.lstSolutionNode.get(index) == edge.getEnd()) {
                    this.lstSolutionNode.remove(index);
                }
            }
        }
    }
    
    public boolean isSolution() {
        if (!this.lstSolutionNode.isEmpty()) {
            if (this.hasTerminals() && this.hasLoop(this.lstSolutionNode.get(0)) && this.isConnected()) {
                return true;
            }
        }
        return false;
    }

    public boolean isConnected() {
        for (int index = 0; index < this.lstSolutionNode.size(); index++) {
            if (!this.visitado[this.lstSolutionNode.get(index)]) {
                return false;
            }
        }
        return true;
    }
    
    public boolean hasTerminals() {
        boolean hasAllTerminals = true;
        for (int indexTerminal = 0; indexTerminal < this.lstTerminal.size(); indexTerminal++) {
            boolean found = false;
            for (int indexSolutionNode = 0; indexSolutionNode < this.lstSolutionNode.size(); indexSolutionNode++) {
                if (this.lstTerminal.get(indexTerminal) == this.lstSolutionNode.get(indexSolutionNode)) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                hasAllTerminals  = false;
                break;
            }
        }
        return hasAllTerminals;
    }
    
    public boolean exist(Edge edge1) {
        for (Edge edge2 : this.lstEdge) {
            if ((edge1.getStart() == edge2.getStart() && edge1.getEnd() == edge2.getEnd() && edge1.getWeight() == edge2.getWeight()) || (edge1.getStart() == edge2.getEnd() && edge1.getEnd() == edge2.getStart() && edge1.getWeight() == edge2.getWeight())) {
                return true;
            }
        }
        return false;
    }
    
    public void trivial(Graph graph) {
        List<Edge> edgeList = graph.getEdgeList();
        int index = 0;
        while(!isSolution()) {
            this.addEdge(edgeList.get(index));
            if (this.hasLoop(edgeList.get(index).getStart())) {
                this.removeEdge(edgeList.get(index));
            }
            index++;
        }
    }
    
    public void createNeighborhood(List<Solution> lstSolution, Graph graph) {
        lstSolution.clear();
        List<Edge> edgeList = graph.getEdgeList();
        for (int index1 = 0; index1 < edgeList.size(); index1++) {
            Edge edge1 = edgeList.get(index1);
            Solution neightbor = new Solution(this);
            if (neightbor.exist(edge1)) {
                neightbor.removeEdge(edge1);
                if (neightbor.isSolution()) {
                    lstSolution.add(neightbor);
                }
                for (int index2 = 0; index2 < edgeList.size(); index2++) {
                    if (index2 == index1) {
                        continue;
                    }
                    Edge edge2 = edgeList.get(index2);
                    if (!neightbor.exist(edge2)) {
                        neightbor.addEdge(edge1);
                        if (neightbor.isSolution()) {
                            lstSolution.add(neightbor);
                        }
                        neightbor.removeEdge(edge2);
                    }
                }
            }
        }
    }
    
    public int getTabuCounter() {
        return this.tabuCounter;
    }
    
    public void setTabuCounter(int value) {
        this.tabuCounter = value;
    }
    
    public void increaseTabuCounter() {
        this.tabuCounter++;
    }

    private List<Integer> getSolutionNodeList() {
        return this.lstSolutionNode;
    }
}
