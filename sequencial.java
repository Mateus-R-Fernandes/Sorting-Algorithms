import java.io.File;
import java.util.Scanner;
import java.io.FileWriter;

public class sequencial 
{
    static class pokemon
    {
        private int id;
        private int gen;
        private String nome;
        private String descripiton;
        private int raridade;
        private double peso;
        private double altura;
        private boolean isLegendary;
        private String data; 
        private String types1;
        private String types2;
        private String habilidades;

        public pokemon(){

        }
        
        public int getId() {
            return id;
        }
        public void setId(int id) {
            this.id = id;
        }
        public int getGen() {
            return gen;
        }
        public void setGen(int gen) {
            this.gen = gen;
        }
        public String getNome() {
            return nome;
        }
        public void setNome(String nome) {
            this.nome = nome;
        }
        public String getDescripiton() {
            return descripiton;
        }
        public void setDescripiton(String descripiton) {
            this.descripiton = descripiton;
        }
        public int getRaridade() {
            return raridade;
        }
        public void setRaridade(int raridade) {
            this.raridade = raridade;
        }
        public double getPeso() {
            return peso;
        }
        public void setPeso(double peso) {
            this.peso = peso;
        }
        public double getAltura() {
            return altura;
        }
        public void setAltura(double altura) {
            this.altura = altura;
        }
        public boolean isLegendary() {
            return isLegendary;
        }
        public void setLegendary(boolean isLegendary) {
            this.isLegendary = isLegendary;
        }
        public String getData() {
            return data;
        }
        public void setData(String data) {
            this.data = data;
        }
        public String getTypes1() {
            return types1;
        }
        public void setTypes1(String types1) {
            this.types1 = types1;
        }
        public String getTypes2() {
            return types2;
        }
        public void setTypes2(String types2) {
            this.types2 = types2;
        }
        public String getHabilidades() {
            return habilidades;
        }
        public void setHabilidades(String habilidades) {
            this.habilidades = habilidades;
        }
    }

    static class TimeLog
    {
        private long start = 0;
        private long end = 0;

        public TimeLog(){

        }
        
        public void setStartTime(){
            this.start = System.currentTimeMillis();
        }

        public void setEndTime(){
            this.end = System.currentTimeMillis();
        }

        public long getTime(){
            return end - start;
            
        }

    }

    public static void ordenacao(pokemon[] poke, int cont)
    {
        TimeLog logTime = new TimeLog();
        logTime.setStartTime();
        int comp = 0;
        int mov = 0;
        for (int i = 0; i < cont - 1; i++) 
        {
            comp++;
            for (int j = 0; j < cont - 1 - i; j++) 
            {
                comp += 2;
                if (poke[j].getNome().compareTo(poke[j + 1].getNome()) > 0) 
                {
                    pokemon temp = poke[j];
                    poke[j] = poke[j + 1];
                    poke[j + 1] = temp;
                    mov++;
                }
            }
        }

        logTime.setEndTime();

        try  
        { 
            FileWriter fw  = new FileWriter("844871_sequencial.txt"); 

            fw.write("844871\t"+comp+"\t"+mov+"\t"+logTime.getTime()); 
            fw.close();
        }
        catch (Exception e) 
        { 
            e.getStackTrace(); 
        } 
    }

    public static String Stringpronta(pokemon generico)
    {
        StringBuilder pronta = new StringBuilder();
                    pronta.append("[#").append(generico.id)
                        .append(" -> ").append(generico.nome)
                        .append(": ").append(generico.descripiton)
                        .append(" - ['").append(generico.types1);

                    pronta.append(generico.types2);
                    

                    pronta.append(" - [").append(generico.habilidades); 

                    pronta.append("] - ").append(generico.peso).append("kg") 
                        .append(" - ").append(generico.altura).append("m") 
                        .append(" - ").append(generico.raridade).append("%");
                        if(generico.isLegendary == false)
                        {
                            pronta.append(" - ").append("false");
                        }
                        else
                        {
                            pronta.append(" - ").append("true");
                        }
                    pronta.append(" - ").append(generico.gen).append(" gen] - ") 
                        .append(generico.data); 

                    String resultado = pronta.toString();

                    return resultado;
    }

    public static pokemon learquivo(String caminho, String nome, pokemon generico)
    {
        
        File pokedex;
        pokedex =  new File(caminho);
        Scanner sc = null;
        boolean condicao = false;

        String line = "";

        try 
        {
            sc = new Scanner(pokedex);

            if (sc.hasNextLine())
            {
                sc.nextLine();
            }

            while (condicao != true && sc.hasNextLine()) 
            {
                line = sc.nextLine();
                
                String[] partes = line.split(",");
                String[] habilidade1 = line.split("\\[");
                String[] habilidade2 = habilidade1[1].split("\\]");
                String[] partes2 = habilidade2[1].split(",");

                generico.setId(Integer.parseInt(partes[0]));
                generico.setNome(partes[2]);
                generico.setDescripiton(partes[3]);
                generico.setTypes1(partes[4]);
                if(partes[5].isEmpty())
                {
                    generico.setTypes2("']");
                }
                else
                {
                    generico.setTypes2("', '"+partes[5]+"']");
                }
               
                generico.setHabilidades(habilidade2[0]);

                if(partes2[1].isEmpty())
                {
                    generico.setPeso(0);
                }
                else
                {
                    generico.setPeso(Double.parseDouble(partes2[1]));
                }

                if(partes2[2].isEmpty())
                {
                    generico.setAltura(0);
                }
                else
                {
                    generico.setAltura(Double.parseDouble(partes2[2]));
                }
                generico.setRaridade(Integer.parseInt(partes2[3]));
                int isLegendary = Integer.parseInt(partes2[4]);
                if(isLegendary == 0){generico.setLegendary(false);}else{generico.setLegendary(true);}
                generico.setData(partes2[5]);
                generico.setGen(Integer.parseInt(partes[1]));

                if (generico.getNome().equals(nome)) 
                {
                    sc.close();
                    return generico;
                }   
            }
        } 
        catch (Exception e) 
        {
            System.out.println("Deu merda ai meu patrao: " + e.getMessage());
        }

        sc.close();
        
        return generico;
    }  

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        //String caminho = "/Users/mateusmac/Projects/AEDS_2/Tp2/pokemon.csv";
        String caminho = "/tmp/pokemon.csv";
        int comp = 0;
        int mov = 0;

        //System.out.println("Digita seu numero ai vai: ");
        String numero = sc.nextLine();
        int [] numeros = new int[100];
 
        pokemon poke[] = new pokemon[100];
        for (int i = 0; i < poke.length; i++) {poke[i] = new pokemon();}

        int cont = 0;

        while (numero.equals("FIM") == false) 
        {
            numeros[cont] = Integer.parseInt(numero);
            
            //System.out.println("Digita seu numero ai vai: ");
            numero = sc.nextLine();
            
            cont++;
        }

        String[] nomes = new String[100];
        int cont2 = 0;
        nomes[cont2] = sc.nextLine();

        while (nomes[cont2].equals("FIM") == false)
        {
            poke[cont2] = learquivo(caminho, nomes[cont2], poke[cont2]);
            
            cont2++;

            //System.out.println("digita o nome do pokemon que vc quer ai vai: ");
            nomes[cont2] = sc.nextLine();
        } 

        TimeLog logTime = new TimeLog();
        logTime.setStartTime();

        for(int i = 0; i<poke.length - 1; i++)
        {
            comp += 2;   
            if(poke[i].getId() != 0)
            {
                boolean tem = false;
                for(int j = 0; j<poke.length - 1; j++)
                {
                    comp += 2; 
                    if(poke[i].getId() == numeros[j])
                    {
                        tem = true;
                        break;
                    }
                    else
                    {
                        tem = false;
                    }
                }
                comp ++; 
                mov++;
                if(tem == true){System.out.println("SIM");}else{System.out.println("NAO");}
            }
        }
        logTime.setEndTime();

        try  
        { 
            FileWriter fw  = new FileWriter("844871_sequencial.txt"); 

            fw.write("844871\t"+comp+"\t"+mov+"\t"+logTime.getTime()); 
            fw.close();
        }
        catch (Exception e) 
        { 
            e.getStackTrace(); 
        } 
        
        sc.close();
    }
}

