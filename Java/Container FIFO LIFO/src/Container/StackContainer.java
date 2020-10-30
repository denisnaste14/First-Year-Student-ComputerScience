package Container;

import model.Task;
import utils.Constants;

public class StackContainer extends AbstractContainer{

    public StackContainer(){
        tasks = new Task[Constants.INITIAL_SIZE_CONTAINER];
        size = 0;
    }

    @Override
    public Task remove() {
        if(!isEmpty()){
            size--;
            return tasks[size];
        }

        return null;
    }

}
