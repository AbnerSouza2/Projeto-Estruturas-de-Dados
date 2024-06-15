#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Contribuicao {
    int mes;
    int ano;
    double valor;
    Contribuicao* proxima;
    Contribuicao(int m, int a, double v) : mes(m), ano(a), valor(v), proxima(NULL) {}
};

struct Participante {
    int id;
    string nome;
    string semestreAno;
    string curso;
    Contribuicao* contribuicoes; 

    Participante() : id(0), nome(""), semestreAno(""), curso(""), contribuicoes(NULL) {}

    Participante(int i, const string& n, const string& sa, const string& c)
        : id(i), nome(n), semestreAno(sa), curso(c), contribuicoes(NULL) {}
};

void cadastrarContribuicao(Participante* participantes, int numParticipantes) {
    int id;
    cout << "Digite o ID do participante: ";
    cin >> id;

   
    Participante* participante = NULL;
    for (int i = 0; i < numParticipantes; ++i) {
        if (participantes[i].id == id) {
            participante = &participantes[i];
            break;
        }
    }

    if (participante == NULL) {
        cout << "Participante com ID " << id << " não encontrado." << endl;
        return;
    }

   
    int mes, ano;
    double valor;
    cout << "Digite o mês da contribuição (1 a 12): ";
    cin >> mes;
    cout << "Digite o ano da contribuição (a partir de 2024): ";
    cin >> ano;
    cout << "Digite o valor da contribuição: ";
    cin >> valor;

    Contribuicao* novaContribuicao = new Contribuicao(mes, ano, valor);

    novaContribuicao->proxima = participante->contribuicoes;
    participante->contribuicoes = novaContribuicao;

    cout << "Contribuição cadastrada com sucesso para o participante " << participante->nome << "." << endl;
}

void inserirParticipante(Participante*& participantes, int& numParticipantes) {
    cout << "Inserir novo participante:" << endl;

    Participante novoParticipante;

    novoParticipante.id = numParticipantes + 1;
    cout << "Nome (primeiro nome): ";
    cin >> novoParticipante.nome;
    cout << "Semestre e ano de ingresso (Ex.: 1/2023): ";
    cin >> novoParticipante.semestreAno;
    cout << "Escolha o curso:" << endl;
    cout << "1. DSM" << endl;
    cout << "2. SI" << endl;
    cout << "3. GE" << endl;
    int escolhaCurso;
    cout << "Opção: ";
    cin >> escolhaCurso;

    switch (escolhaCurso) {
        case 1:
            novoParticipante.curso = "DSM";
            break;
        case 2:
            novoParticipante.curso = "SI";
            break;
        case 3:
            novoParticipante.curso = "GE";
            break;
        default:
            cout << "Opção inválida. Curso definido como DSM por padrão." << endl;
            novoParticipante.curso = "DSM";
            break;
    }

    Participante* novoArray = new Participante[numParticipantes + 1];
    for (int i = 0; i < numParticipantes; ++i) {
        novoArray[i] = participantes[i];
    }
    novoArray[numParticipantes] = novoParticipante;

    delete[] participantes;
    participantes = novoArray;
    numParticipantes++;

    cout << "Participante inserido com sucesso." << endl;
}

void editarParticipante(Participante* participantes, int numParticipantes) {
    int idEditar;
    cout << "Digite o ID do participante a ser editado: ";
    cin >> idEditar;

    Participante* participante = NULL;
    for (int i = 0; i < numParticipantes; ++i) {
        if (participantes[i].id == idEditar) {
            participante = &participantes[i];
            break;
        }
    }

    if (participante == NULL) {
        cout << "Participante com ID " << idEditar << " não encontrado." << endl;
        return;
    }

    cout << "Editar dados do participante ID " << idEditar << ":" << endl;

    cout << "Nome atual: " << participante->nome << endl;
    cout << "Novo nome: ";
    cin >> participante->nome;

    cout << "Semestre e ano atual: " << participante->semestreAno << endl;
    cout << "Novo semestre e ano: ";
    cin >> participante->semestreAno;

    cout << "Curso atual: " << participante->curso << endl;
    cout << "Novo curso:" << endl;
    cout << "1. DSM" << endl;
    cout << "2. SI" << endl;
    cout << "3. GE" << endl;
    int escolhaCurso;
    cout << "Opção: ";
    cin >> escolhaCurso;

    switch (escolhaCurso) {
        case 1:
            participante->curso = "DSM";
            break;
        case 2:
            participante->curso = "SI";
            break;
        case 3:
            participante->curso = "GE";
            break;
        default:
            cout << "Opção inválida. Mantendo o curso atual." << endl;
            break;
    }

    cout << "Dados atualizados com sucesso!" << endl;
}



void lerParticipantes(Participante*& participantes, int& numParticipantes) {
    ifstream arquivo("participantes.txt");

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo participantes.txt" << endl;
        return;
    }

    if (participantes != NULL) {
        delete[] participantes;
        participantes = NULL;
        numParticipantes = 0;
    }

    string linha;
    while (getline(arquivo, linha)) {
        stringstream ss(linha);
        Participante novoParticipante;

        string token;
        getline(ss, token, ',');
        stringstream converter(token);
        converter >> novoParticipante.id;

        getline(ss, novoParticipante.nome, ',');
        getline(ss, novoParticipante.semestreAno, ',');
        getline(ss, novoParticipante.curso);

        Participante* novoArray = new Participante[numParticipantes + 1];
        for (int i = 0; i < numParticipantes; ++i) {
            novoArray[i] = participantes[i];
        }
        novoArray[numParticipantes] = novoParticipante;

        delete[] participantes;
        participantes = novoArray;
        numParticipantes++;
    }

    arquivo.close();
    cout << "Leitura de participantes concluída." << endl;
}



void gravarParticipantes(Participante* participantes, int numParticipantes) {
    ofstream arquivo("participantes.txt");

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo participantes.txt para escrita." << endl;
        return;
    }

    for (int i = 0; i < numParticipantes; ++i) {
        arquivo << participantes[i].id << ","
                << participantes[i].nome << ","
                << participantes[i].semestreAno << ","
                << participantes[i].curso << endl;
    }

    arquivo.close();
    cout << "Dados gravados em participantes.txt com sucesso." << endl;
}

void liberarMemoria(Participante* participantes, int numParticipantes) {
    for (int i = 0; i < numParticipantes; ++i) {
        Contribuicao* current = participantes[i].contribuicoes;
        while (current != NULL) {
            Contribuicao* next = current->proxima;
            delete current;
            current = next;
        }
    }

    delete[] participantes;
}

void gravarContribuintesGlobal(Participante* participantes, int numParticipantes) {
    ofstream arquivo("contribuintes.txt");

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo contribuintes.txt para escrita." << endl;
        return;
    }

    for (int i = 0; i < numParticipantes; ++i) {
        arquivo << "ID: " << participantes[i].id << ", Nome: " << participantes[i].nome
                << ", Curso: " << participantes[i].curso << endl;
        arquivo << "Contribuições:" << endl;

        Contribuicao* contribuicaoAtual = participantes[i].contribuicoes;
        while (contribuicaoAtual != NULL) {
            arquivo << "  Mês: " << contribuicaoAtual->mes
                    << ", Ano: " << contribuicaoAtual->ano
                    << ", Valor: " << contribuicaoAtual->valor << endl;
            contribuicaoAtual = contribuicaoAtual->proxima;
        }

        arquivo << endl;
    }

    arquivo.close();
    cout << "Dados gravados em contribuintes.txt com sucesso." << endl;
}


void gravarContribuintesPorCurso(Participante* participantes, int numParticipantes) {
    ofstream arquivoDSM("contribuintes_DSM.txt");
    ofstream arquivoSI("contribuintes_SI.txt");
    ofstream arquivoGE("contribuintes_GE.txt");

    if (!arquivoDSM.is_open() || !arquivoSI.is_open() || !arquivoGE.is_open()) {
        cerr << "Erro ao abrir os arquivos para escrita." << endl;
        return;
    }

    for (int i = 0; i < numParticipantes; ++i) {
        if (participantes[i].curso == "DSM") {
            arquivoDSM << "ID: " << participantes[i].id << ", Nome: " << participantes[i].nome
                       << ", Curso: " << participantes[i].curso << endl;
            arquivoDSM << "Contribuições:" << endl;

            Contribuicao* contribuicaoAtual = participantes[i].contribuicoes;
            while (contribuicaoAtual != NULL) {  
                arquivoDSM << "  Mês: " << contribuicaoAtual->mes
                           << ", Ano: " << contribuicaoAtual->ano
                           << ", Valor: " << contribuicaoAtual->valor << endl;
                contribuicaoAtual = contribuicaoAtual->proxima;
            }

            arquivoDSM << endl;
        }
        else if (participantes[i].curso == "SI") {
            arquivoSI << "ID: " << participantes[i].id << ", Nome: " << participantes[i].nome
                      << ", Curso: " << participantes[i].curso << endl;
            arquivoSI << "Contribuições:" << endl;

            Contribuicao* contribuicaoAtual = participantes[i].contribuicoes;
            while (contribuicaoAtual != NULL) {  // <-- Substituí nullptr por NULL aqui
                arquivoSI << "  Mês: " << contribuicaoAtual->mes
                          << ", Ano: " << contribuicaoAtual->ano
                          << ", Valor: " << contribuicaoAtual->valor << endl;
                contribuicaoAtual = contribuicaoAtual->proxima;
            }

            arquivoSI << endl;
        }
        else if (participantes[i].curso == "GE") {
            arquivoGE << "ID: " << participantes[i].id << ", Nome: " << participantes[i].nome
                      << ", Curso: " << participantes[i].curso << endl;
            arquivoGE << "Contribuições:" << endl;

            Contribuicao* contribuicaoAtual = participantes[i].contribuicoes;
            while (contribuicaoAtual != NULL) { 
                arquivoGE << "  Mês: " << contribuicaoAtual->mes
                          << ", Ano: " << contribuicaoAtual->ano
                          << ", Valor: " << contribuicaoAtual->valor << endl;
                contribuicaoAtual = contribuicaoAtual->proxima;
            }

            arquivoGE << endl;
        }
    }

    arquivoDSM.close();
    arquivoSI.close();
    arquivoGE.close();
    cout << "Dados gravados em arquivos por curso com sucesso." << endl;
}



int main() {
    setlocale(LC_ALL, "portuguese");

    Participante* participantes = NULL;
    int numParticipantes = 0;
    int escolha;


    lerParticipantes(participantes, numParticipantes);

    do {
        cout << "\nMenu Principal:" << endl;
        cout << "1) Quem são os participantes da comunidade?" << endl;
        cout << "2) Inserir novo participante" << endl;
        cout << "3) Editar dados de um participante" << endl;
        cout << "4) Cadastrar contribuição" << endl;
        cout << "5) Ler dados de participantes de arquivo" << endl;
        cout << "6) Gravar dados de participantes em arquivo" << endl;
        cout << "7) Gravar todos os contribuintes em arquivo-texto (contribuintes.txt)" << endl;
        cout << "8) Gravar contribuintes por curso em arquivos separados" << endl;
        cout << "0) Sair" << endl;
        cout << "Escolha: ";
        cin >> escolha;

        switch (escolha) {
            case 1:
  
    if (numParticipantes == 0) {
        cout << "Nenhum participante cadastrado." << endl;
    } else {
        cout << "Lista de participantes:" << endl;
        for (int i = 0; i < numParticipantes; ++i) {
            cout << "ID: " << participantes[i].id << endl;
            cout << "Nome: " << participantes[i].nome << endl;
            cout << "Semestre e ano: " << participantes[i].semestreAno << endl;
            cout << "Curso: " << participantes[i].curso << endl;

          
            Contribuicao* contribuicaoAtual = participantes[i].contribuicoes;
            if (contribuicaoAtual != NULL) {
                cout << "Contribuições:" << endl;
                while (contribuicaoAtual != NULL) {
                    cout << "  Mês: " << contribuicaoAtual->mes
                         << ", Ano: " << contribuicaoAtual->ano
                         << ", Valor: " << contribuicaoAtual->valor << endl;
                    contribuicaoAtual = contribuicaoAtual->proxima;
                }
            } else {
                cout << "Este participante não possui contribuições cadastradas." << endl;
            }

            cout << endl;
        }
    }
    break;



            case 2:
                inserirParticipante(participantes, numParticipantes);
                break;
            case 3:
                editarParticipante(participantes, numParticipantes);
                break;
            case 4:
                cadastrarContribuicao(participantes, numParticipantes);
                break;
            case 5:
                lerParticipantes(participantes, numParticipantes); 
                break;
            case 6:
                gravarParticipantes(participantes, numParticipantes);
                break;
            case 7:
                gravarContribuintesGlobal(participantes, numParticipantes);
                break;
            case 8:
                gravarContribuintesPorCurso(participantes, numParticipantes);
                break;
            case 0:
                cout << "Encerrando o programa..." << endl;
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
                break;
        }
    } while (escolha != 0);

    
    gravarParticipantes(participantes, numParticipantes);

    liberarMemoria(participantes, numParticipantes);

    return 0;
}

