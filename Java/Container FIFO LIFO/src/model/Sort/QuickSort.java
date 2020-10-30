package model.Sort;
import model.Task;

public class QuickSort {
    private int[] c;

    public QuickSort(int[] c){
        this.c=c;
    }
    private int partition(int[] c, int low, int high){
        int i=(low-1);
        int pivot=c[high];
        for(int j=low;j<high;j++) {
            if (c[j]<pivot) {
                i++;
                int aux=c[i];
                c[i]=c[j];
                c[j]=aux;
            }
        }
        int aux=c[i+1];
        c[i+1]=c[high];
        c[high]=aux;
        return i+1;
    }

    private void sort(int[] c, int low, int high){
        if(low < high){
            int pi=partition(c,low,high);
            sort(c,low,pi-1);
            sort(c,pi+1,high);
        }
    }
    public int[] quick_sort(){
        sort(c,0,c.length-1);
        return c;
    }
}
