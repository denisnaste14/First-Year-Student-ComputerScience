package model;

import Factory.Strategy;
import model.Sort.SortingStrategy;
import model.Sort.SortingTask;
import runner.PrinterTaskRunner;
import runner.StrategyTaskRunner;
import runner.DelayTaskRunner;

import java.time.LocalDateTime;

public class TestRunner {
    public static void main(String[] args){
        /* MessageTask t1 = new MessageTask("1", "feedback", "Good job", "Gigi", "Ana", LocalDateTime.now());
        MessageTask t2 = new MessageTask("2", "response", "Thanks", "Ana", "Gigi", LocalDateTime.now());
        MessageTask[] tasks = new MessageTask[]{t1, t2};
       for(var el : tasks){
            el.execute();
        }

        StrategyTaskRunner runner = new StrategyTaskRunner(Strategy.LIFO);
        runner.addTask(tasks[1]);
        runner.addTask(tasks[0]);
        //runner.executeAll();

        PrinterTaskRunner decorator = new PrinterTaskRunner(runner);
        decorator.executeAll();*/
        int[] array_s1={12,3,38,1,6,44,7,3,10};
        SortingTask s1 = new SortingTask("1","metoda bulelor",SortingStrategy.BUBBLESORT,array_s1);
        SortingTask s2 = new SortingTask("2","metoda quicksort",SortingStrategy.QUICKSORT,array_s1);
        SortingTask[] tasks=new SortingTask[]{s1,s2};
        /*for(var task:tasks){
            task.execute();
        }*/
        StrategyTaskRunner runner = new StrategyTaskRunner(Strategy.LIFO);
        runner.addTask(tasks[1]);
        runner.addTask(tasks[0]);
        DelayTaskRunner decorator=new DelayTaskRunner(new DelayTaskRunner(new DelayTaskRunner(runner)));
        decorator.executeAll();
    }
}
