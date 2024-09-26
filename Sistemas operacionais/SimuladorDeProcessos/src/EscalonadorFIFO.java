import java.util.Queue;           // Para a interface Queue (utilizada no FIFO)
import java.util.LinkedList;      // Para a implementação de LinkedList (utilizada no FIFO)


class EscalonadorFIFO {

    // Fila para armazenar os processos
    Queue<Processo> filaProcessos = new LinkedList<>();

    // Adiciona processos na fila
    public void adicionarProcesso(Processo processo) {
        filaProcessos.add(processo);
        System.out.println("Processo " + processo.pid + " adicionado.");
    }

    // Executa os processos na ordem FIFO
    public void executar() {
        System.out.println("\nEscalonamento FIFO:");
        while (!filaProcessos.isEmpty()) {
            Processo processo = filaProcessos.poll();  // Remove o processo da fila
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
