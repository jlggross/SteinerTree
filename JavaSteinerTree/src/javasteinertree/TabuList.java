package javasteinertree;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author jlggross
 */
public class TabuList {
   
    final int BT_MAX = 40;
    final int TABU_SIZE = 10;
    final int TABU_TIME = 15;
    final int MAX_EVALUATION = 999999999;

    protected Solution optimal;
    protected List<Solution> tabus = new ArrayList<>();
    
    /* 
     * Class constructor
     */
    public TabuList() {
        this.optimal.setEvaluation(MAX_EVALUATION);
    }
    
    /* 
     * Checks if the tabu list has the given element
     */  
    public boolean hasItem(Solution s) {
        int evaluation = s.getEvaluation();
        for (Solution t : this.tabus) {
            if (evaluation == t.getEvaluation()) {
                return true;
            }
        }
        
        return false;
    }
    
    /* 
     * Inserts an element in the tabu list
     */
    public void insertTabu(Solution s) {
        s.setTabuCounter(TABU_TIME);
        this.tabus.add(s);
        
        if (tabus.size() == TABU_SIZE) {
            tabus.remove(0);  //Original: tabus.erase( tabus.begin() );
        }
    }
    
    /* 
     * Updates solution "ótima"
     */
    public boolean updateOptimal(Solution s) {
        if (s.getEvaluation() < this.optimal.getEvaluation()) {
            this.optimal = s;
            return true;
        }
        
        return false;
    }
    
    /* 
     * Prints Tabu List
     */
    public void printTabuList() {
        System.out.print("Lista Tabu = ");
        for (Solution s : this.tabus) {
            System.out.print(s.getEvaluation() + " ");
        }
    }
    
    public void round() {
        int count = -1;
        for (Solution s : this.tabus) {
            count++;
            if (s.getTabuCounter() > TABU_TIME) {
                this.tabus.remove(count);
            }
        }
    }
    
    public Solution getOptimal() {
        return this.optimal;
    }
    
}
