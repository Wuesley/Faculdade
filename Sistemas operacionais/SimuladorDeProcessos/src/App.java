public class App {

    public static void main(String[] args) {

        // Cria processos com diferentes tempos de execução
        Processo p1 = new Processo(1, 5);   // Processo 1 - 5 segundos
        Processo p2 = new Processo(2, 2);   // Processo 2 - 2 segundos
        Processo p3 = new Processo(3, 8);   // Processo 3 - 8 segundos
        Processo p4 = new Processo(4, 3);   // Processo 4 - 3 segundos


        //vetor de processo ?
        // sorteio as ordens deles ?

        // FIFO (o primeiro que chegar é a mulher do padre kkkk)
        EscalonadorFIFO fifo = new EscalonadorFIFO();
        fifo.adicionarProcesso(p1);
        fifo.adicionarProcesso(p2);
        fifo.adicionarProcesso(p3);
        fifo.adicionarProcesso(p4);
        fifo.executar();

        // SJF (quem tem o menor tempo de processamento entra na fila)
        EscalonadorSJF sjf = new EscalonadorSJF();
        sjf.adicionarProcesso(p1);
        sjf.adicionarProcesso(p2);
        sjf.adicionarProcesso(p3);
        sjf.adicionarProcesso(p4);
        sjf.executar();
    }
}


