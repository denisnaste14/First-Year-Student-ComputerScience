package model;

import java.util.Objects;

public abstract class Task {
    private String taskId, description;

    public Task(String taskId, String description) {
        this.taskId = taskId;
        this.description = description;
    }

    public String getTaskId() {
        return taskId;
    }

    public String getDescription() {
        return description;
    }

    public void setTaskId(String taskId) {
        this.taskId = taskId;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    /** abstract methods */

    public abstract void execute();


    /** override */

    @Override
    public String toString(){
        return taskId + " " + description;
    }

    @Override
    public boolean equals(Object obj){
        if (this == obj)
            return true;

        if (!(obj instanceof Task))
            return false;

        Task t = (Task) obj;

        return Objects.equals(getTaskId(), t.getTaskId()) && Objects.equals(getDescription(), t.getDescription());
    }

    @Override
    public int hashCode(){
        return Objects.hash(getTaskId(), getDescription());
    }
}
