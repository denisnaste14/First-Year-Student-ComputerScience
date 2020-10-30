package model.Sort;
import model.Task;
import Container.Container;
public class SortingTask extends Task {

    private final SortingStrategy sortingStrategy;
    private int[] c;
    public SortingTask(String taskID, String description, SortingStrategy sortingStrategy, int[] c){
       super(taskID,description);
       this.sortingStrategy=sortingStrategy;
       this.c=c;
    }

    private void sort(){
        if(sortingStrategy==SortingStrategy.BUBBLESORT){
            BubbleSort bubble = new BubbleSort(c);
            c=bubble.bubble_sort();  // sorteaza containerul
        }
        else{
            if(sortingStrategy==SortingStrategy.QUICKSORT){
                QuickSort quick = new QuickSort(c);
                c=quick.quick_sort();
            }
        }
    }
    private void print_sorted_array(){
        int i;
        for(i=0;i<c.length;i++){
            System.out.print(c[i]);
            System.out.print(" ");
        }
        System.out.println("\n");
    }
    @Override
    public void execute(){
        sort();
        print_sorted_array();
    }
}
