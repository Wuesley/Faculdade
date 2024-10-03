import classes.Process;
import classes.ProcessTableFIFO;
import classes.ProcessTableSJF;

public class Main {
    public static void main(String[] args) {
        Process p0 = new Process(0, 10000);
        Process p1 = new Process(1, 5000);
        Process p2 = new Process(2, 7000);
        Process p3 = new Process(3, 3000);
        Process p4 = new Process(4, 3000);
        Process p5 = new Process(5, 8000);
        Process p6 = new Process(6, 2000);
        Process p7 = new Process(7, 5000);
        Process p8 = new Process(8, 4000);
        Process p9 = new Process(9, 10000);

        Process[] processes = {p0, p1, p2, p3, p4, p5, p6, p7, p8, p9};

        // Primeira etapa: escalonamento FIFO
        System.out.println("Escalonamento FIFO:");
        ProcessTableFIFO fifoTable = new ProcessTableFIFO(processes);
        final int QUANTUM = 1000;
        Process current;
        int lineCount = 0;

        System.out.println("-".repeat(150));
        System.out.printf("%-20s%-30s%-20s%-20s%-20s%-20s%s%n", "PID", "Executed Processing Time", "PC", "State", "I/O",
                "CPU", "Transition");
        System.out.println("-".repeat(150));

        while (fifoTable.isThereProcessNotTerminated() && lineCount < 30) {
            current = fifoTable.next(); // FIFO escalonamento

            if (current.isWaiting()) {
                current.checkIfDataIsAvailable();
                System.out.println(current.toTableFormat() + " WAITING -> " + current.getState());
                lineCount++;
                continue;
            }

            current.run();
            System.out.println(current.toTableFormat() + " READY -> RUNNING");
            lineCount++;

            for (int i = 0; i < QUANTUM; i++) {
                current.process();
                if (current.isTerminated() || current.isWaiting()) {
                    break;
                }
            }

            if (current.isRunning()) {
                current.getReady();
            }
            System.out.println(current.toTableFormat() + " RUNNING -> " + current.getState());
            lineCount++;
        }

        // Reiniciando os processos
        for (Process p : processes) {
            p.resetProcess();
        }

        // Segunda etapa: escalonamento SJF
        System.out.println("\nEscalonamento SJF:");
        ProcessTableSJF sjfTable = new ProcessTableSJF(processes);
        lineCount = 0; // Resetando contagem de linhas

        System.out.println("-".repeat(150));
        System.out.printf("%-20s%-30s%-20s%-20s%-20s%-20s%s%n", "PID", "Executed Processing Time", "PC", "State", "I/O",
                "CPU", "Transition");
        System.out.println("-".repeat(150));

        while (sjfTable.isThereProcessNotTerminated() && lineCount < 30) {
            current = sjfTable.next(); // SJF escalonamento

            if (current.isWaiting()) {
                current.checkIfDataIsAvailable();
                System.out.println(current.toTableFormat() + " WAITING -> " + current.getState());
                lineCount++;
                continue;
            }

            current.run();
            System.out.println(current.toTableFormat() + " READY -> RUNNING");
            lineCount++;

            for (int i = 0; i < QUANTUM; i++) {
                current.process();
                if (current.isTerminated() || current.isWaiting()) {
                    break;
                }
            }

            if (current.isRunning()) {
                current.getReady();
            }
            System.out.println(current.toTableFormat() + " RUNNING -> " + current.getState());
            lineCount++;
        }
    }
}
