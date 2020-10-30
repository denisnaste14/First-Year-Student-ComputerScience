package runner;
import java.util.concurrent.TimeUnit;
import java.time.LocalDateTime;
import utils.Constants;

public class DelayTaskRunner extends AbstractTaskRunner{
    public DelayTaskRunner(TaskRunner runner){
        super(runner);
    }

    @Override
    public void executeOneTask(){
        try {
            TimeUnit.SECONDS.sleep(Constants.DELAY_SECOUNDS);
            runner.executeOneTask();
        }catch(InterruptedException e){
            e.printStackTrace();
        }
        decorateExecuteOneTask();
    }
    public void decorateExecuteOneTask(){
        System.out.println("Task executat:" + LocalDateTime.now().format(Constants.DATE_TIME_FORMATTER)+" cu un delay de "+String.valueOf(Constants.DELAY_SECOUNDS)+" secunde.");
    }
}
