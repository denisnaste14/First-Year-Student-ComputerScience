package Container;
import model.Task;
import utils.Constants;

public class QueueContainer extends AbstractContainer{

    public QueueContainer() {
        size=0;
        tasks=new Task[Constants.INITIAL_SIZE_CONTAINER];
    }

    @Override
    public Task remove(){
        if(!isEmpty()) {
            Task save;
            save=tasks[0];
            //aduc elementele in stanga cu cate o pozitie astfel acoperind elementul prim (FIFO)
            for(int i=0;i<size-1;i++)
                tasks[i]=tasks[i+1];
            size--;
            return save;
        }
        return null;
    }

}
