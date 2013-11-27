package javasteinertree;

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author jlggross
 */
public class TabuList {
   
    protected final int BT_MAX = 40;
    protected final int TABU_SIZE = 10;
    protected final int TABU_TIME = 15;
    protected final int MAX_EVALUATION = 999999999;

    protected Solution otima;
    protected List<Solution> tabus = new ArrayList<>();
    
    /* 
     * Class constructor
     */
    public TabuList() {
        this.otima.setEvaluation(MAX_EVALUATION);
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
    public boolean updateOtima(Solution s) {
        if (s.getEvaluation() < this.otima.getEvaluation()) {
            this.otima = s;
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
    
}
