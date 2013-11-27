package javasteinertree;

import java.util.ArrayList;
import java.util.List;

public class Search {
    
    protected final int MAX_ITERATIONS = 100;
    
    /* 
     * Do a deterministic local search.
     * Searches for the best solution in its neighbors.
     */    
    public Solution searchBestLocal(Solution initial, Graph g, int iterations) { 
      if (iterations < MAX_ITERATIONS) {
          List<Solution> neighbors = new ArrayList<>();
          initial.createNeighborhood(neighbors, g);
          
          int lessPosition = -1;
          int less = initial.getEvaluation();
          
          int count = -1;
          for (Solution s : neighbors) {
              count++;
              int valued = s.getEvaluation();
              if (valued < less) {
                  less = valued;
                  lessPosition = count;
              }
          }
          
          if (lessPosition == -1) {
              return initial;
          } else {
              return searchBestLocal(neighbors.get(lessPosition), g, iterations+1);
          }               
      } else {
          return initial;
      }   
    }
    
    /* 
     * Do a local search.
     * Goes for the first best solution.
     */  
    public Solution searchFirstLocal(Solution initial, Graph g, int iterations) {
        if (iterations < MAX_ITERATIONS) {
            List<Solution> neighbors = new ArrayList<>();
            initial.createNeighborhood(neighbors, g);
            
            int less = initial.getEvaluation();
            for (Solution s : neighbors) {
                int valued = s.getEvaluation();
                if (valued < less) {
                    return searchFirstLocal(s, g, iterations + 1);
                }
            }
            return initial;
        } else {
            return initial;
        }
    }
    
    /* 
     * Do a tabu search.
     * Goes for the first best solution.
     * Uses a list of forbeidens (tabu).
     */  
    public Solution tabuSearch(Solution initial, Graph g, int iterations, TabuList tabuList) {
        while (iterations < TabuList.BT_MAX) {
            tabuList.printTabuList();
            
            List<Solution> neighbors = new ArrayList<>();
            initial.createNeighborhood(neighbors, g);
            
            System.out.println("neighbors = ");
            
            tabuList.insertTabu(initial);
            int less = initial.getEvaluation();
            int size = neighbors.size();
            int indLess = -1;
            boolean found = false;
            
            int count = -1;
            for (Solution s : neighbors) {
                count++;
                int valued = s.getEvaluation();
                if (valued < less && !tabuList.hasItem(s)) {
                    less = valued;
                    indLess = count;
                }
            }
            
            if (indLess != -1) {
                if (tabuList.updateOptimal(neighbors.get(indLess))) {
                    initial = neighbors.get(indLess);
                    iterations = 0;
                    System.out.println("Found a better solution!");
                } else {
                    initial = neighbors.get(indLess);
                    iterations++;
                }
            } 
            
            /* if there is not a neighbor with a better solution than the
             * initial solution, we insert the initial solution in the tabu
             * list and continue the search with the first possible solution.
             */
            else {
                
            }
        }
        
        return tabuList.getOptimal();
    }
}
