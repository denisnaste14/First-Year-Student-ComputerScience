package Factory;

import Container.Container;
import Container.StackContainer;
import Container.QueueContainer;

public class TaskContainerFactory implements Factory{
    private static TaskContainerFactory instance = null;
    private TaskContainerFactory() {

    }

    public static TaskContainerFactory getInstance(){
        if(instance == null){
            instance = new TaskContainerFactory();
        }
        return instance;
    }

    @Override
    public Container createContainer(Strategy strategy) {
        if(strategy == Strategy.LIFO)
            return new StackContainer();
        if(strategy == Strategy.FIFO)
            return new QueueContainer();
        return null;
    }
}
