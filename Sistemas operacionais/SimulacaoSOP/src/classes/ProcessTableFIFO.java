package classes;

import java.util.LinkedList;
import java.util.Queue;

public class ProcessTableFIFO {
    private final Queue<Process> queue;

    public ProcessTableFIFO(Process... processes) {
        this.queue = new LinkedList<>();
        for (Process p : processes) {
            queue.offer(p);
        }
    }

    public Process next() {
        return queue.peek(); // Retorna o próximo processo da fila sem removê-lo
    }

    public void rotate() {
        // Remove o processo da frente da fila e o coloca no final (rotação de processos)
        Process p = queue.poll();
        if (!p.isTerminated()) {
            queue.offer(p);
        }
    }

    public boolean isThereProcessNotTerminated() {
        for (Process p : queue) {
            if (!p.isTerminated()) {
                return true;
            }
        }
        return false;
    }
}
