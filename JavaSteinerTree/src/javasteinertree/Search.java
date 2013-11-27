package javasteinertree;

import java.util.ArrayList;
import java.util.List;

public class Search {
    
    protected final int MAX_ITERATIONS = 100;
    
    /* 
     * Do a deterministic local seach.
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
    
    
    
    
}
