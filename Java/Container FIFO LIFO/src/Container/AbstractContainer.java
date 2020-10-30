package Container;
import model.Task;
import utils.Constants;

public abstract class AbstractContainer implements Container{
    public abstract Task remove();
    public int size;
    public Task[] tasks;

    public AbstractContainer(){
        size=0;
        tasks=new Task[Constants.INITIAL_SIZE_CONTAINER];
    }

    @Override
    public void add(Task task) {
        if(tasks.length == size){
            Task[] t = new Task[tasks.length * 2];
            System.arraycopy(tasks, 0, t,0,tasks.length);
            tasks = t;
        }
        tasks[size++] = task;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public boolean isEmpty() {
        return size == 0;
    }

    @Override
    public Task at(int index){
        if(index<0 || index>=size)
            return null;
        return tasks[index];
    }
}
