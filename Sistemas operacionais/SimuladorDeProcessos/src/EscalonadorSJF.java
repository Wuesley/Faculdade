import java.util.PriorityQueue;
import java.util.Comparator;


public class EscalonadorSJF {

    // PriorityQueue para ordenar os processos com base no tempo de execução
    PriorityQueue<Processo> filaProcessos = new PriorityQueue<>(Comparator.comparingInt(p -> p.tempoExecucao));

    // Adiciona processos na fila
    public void adicionarProcesso(Processo processo) {
        filaProcessos.add(processo);
        System.out.println("Processo " + processo.pid + " adicionado.");
    }

    // Executa os processos com base no menor tempo de execução
    public void executar() {
        System.out.println("\nEscalonamento SJF:");
        while (!filaProcessos.isEmpty()) {
            Processo processo = filaProcessos.poll();  // Remove o processo com menor tempo de execução
            System.out.println("Executando " + processo);
            // Simula o tempo de execução (para simplificar, só mostra no console)
            try {
                Thread.sleep(processo.tempoExecucao * 100);  // Multiplica por 100 para simular o tempo
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Processo " + processo.pid + " finalizado.");
        }
    }
}
