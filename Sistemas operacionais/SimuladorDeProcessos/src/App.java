import java.util.ArrayList;

public class App {

    public static void main(String[] args) {

        // Criamos os processos
        Processo p1 = new Processo(1, 5);   // Processo 1 - 5 segundos
        Processo p2 = new Processo(2, 2);   // Processo 2 - 2 segundos
        Processo p3 = new Processo(3, 8);   // Processo 3 - 8 segundos
        Processo p4 = new Processo(4, 3);   // Processo 4 - 3 segundos

        // Precisamos de um arraylist de processo que serão executados?
        // usaremos o tempo de chegada para executar os processos

        ArrayList<Processo> lista_de_processos = new ArrayList<>();

        public Processo entradaDoProcesso(){
            lista_de_processos.add(p1);
        }









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


