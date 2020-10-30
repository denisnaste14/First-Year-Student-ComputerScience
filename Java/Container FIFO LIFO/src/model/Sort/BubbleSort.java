package model.Sort;

public class BubbleSort {
    private int[] c;
    public BubbleSort(int[] c){
        this.c=c;
    }

    public int[] bubble_sort(){
        boolean sorted;
        do{
            sorted=true;
            for(int i=0;i<c.length-1;i++){
                if(c[i]>c[i+1]){
                    sorted=false;
                    int aux=c[i];
                    c[i]=c[i+1];
                    c[i+1]=aux;
                }
            }
        }while(!sorted);
        return c;
    }
}
