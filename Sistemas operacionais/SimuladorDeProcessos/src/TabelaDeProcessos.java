import java.util.Collections;
import java.util.List;
import java.util.ArrayList;

    public class TabelaDeProcessos{
        private final List<Processo> tabela;
        private int index;

        {
            tabela = new ArrayList<>();
        }

        public ProcessTable(Processo... processes) {
            Collections.addAll(tabela, processes);
        }

        public Processo next() {
            Processo p;
            int tabelaSize = tabela.size();
            for (int i = 0; i < tabelaSize; i++) {
                p = tabela.get(index);
                index = index < tabelaSize - 1 ? index + 1 : 0;
                if (!p.isTerminated()) {
                    return p;
                }
            }
            return null;
        }

        public boolean isThereProcessNotTerminated() {
            for (Processo p : tabela) {
                if (!p.isTerminated()) {
                    return true;
                }
            }
            return false;
        }
    }

