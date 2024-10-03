package classes;

import java.util.List;

public class Scheduler {
    private final List<Process> processes;

    public Scheduler(List<Process> processes) {
        this.processes = processes;
    }

    public void executeFIFO() {
        for (Process process : processes) {
            process.run();
            while (!process.isTerminated()) {
                process.process();
                System.out.println(process.toTableFormat());
            }
            process.resetProcess(); // Reinicia o processo após a execução
        }
    }

    public void executeSJF() {
        ProcessTableSJF tableSJF = new ProcessTableSJF(processes.toArray(new Process[0]));

        while (tableSJF.isThereProcessNotTerminated()) {
            Process nextProcess = tableSJF.next();
            if (nextProcess != null) {
                nextProcess.run();
                while (!nextProcess.isTerminated()) {
                    nextProcess.process();
                    System.out.println(nextProcess.toTableFormat());
                }
                nextProcess.resetProcess(); // Reinicia o processo após a execução
            }
        }
    }

    public void run() {
        System.out.println("Executando FIFO...");
        executeFIFO();
        System.out.println("Executando SJF...");
        executeSJF();
    }
}
