package classes;

import java.util.ArrayList;
import java.util.List;

public class ProcessTableSJF {
    private final List<Process> table;

    public ProcessTableSJF(Process... processes) {
        this.table = new ArrayList<>();
        for (Process p : processes) {
            table.add(p);
        }
    }

    public Process next() {
        Process shortestJob = null;
        for (Process p : table) {
            if (!p.isTerminated()) {
                if (shortestJob == null || p.getRemainingProcessingTime() < shortestJob.getRemainingProcessingTime()) {
                    shortestJob = p;
                }
            }
        }
        return shortestJob; // Retorna o processo com o menor tempo restante
    }

    public boolean isThereProcessNotTerminated() {
        for (Process p : table) {
            if (!p.isTerminated()) {
                return true;
            }
        }
        return false;
    }
}
