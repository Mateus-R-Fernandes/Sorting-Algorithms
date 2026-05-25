import java.io.File;
import java.util.Scanner;import java.io.FileWriter; 

public class Insercao
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

    public static int comparadata(pokemon um, pokemon dois)
    {
        String[] data = new String[3];
        String[] data2 = new String[3];

        data = um.getData().split("/");
        data2 = dois.getData().split("/");

        if(Integer.parseInt(data2[2]) > Integer.parseInt(data[2]))
        {
            return -39;
        }
        else
        {
            if (Integer.parseInt(data2[2]) < Integer.parseInt(data[2])){return 9586;}
            if(Integer.parseInt(data2[1]) > Integer.parseInt(data[1]))
            {
                return -87;
            }
            else
            {
                if (Integer.parseInt(data2[1]) < Integer.parseInt(data[1])){return 16;}
                if(Integer.parseInt(data2[0]) > Integer.parseInt(data[0]) && Integer.parseInt(data2[1]) == Integer.parseInt(data[1]))
                {
                    return -2;
                }
            }
        }

        return 72;
    } 

    public static void ordenacao(pokemon arr[], int tam) 
    {
        TimeLog logTime = new TimeLog();
        int comp = 0;
        int mov = 0;

        logTime.setStartTime();

        pokemon key;
        int n = tam;
        for (int i = 1; i < n; i++) 
        {
            comp++;
            key = arr[i];
            int j = i - 1;
    
            while (j >= 0 && comparadata(arr[j], key) > 0)
            {
                mov++;
                comp++;
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }

        logTime.setEndTime();

        for(int i = tam - 1; i>=0; i--)
        {
            for(int j = tam - 1; j>=0; j--)
            {
                if(arr[j].id != 0)
                {
                    if(arr[i].getData().equals(arr[j].getData()))
                    {
                        if (arr[i].getNome().compareTo(arr[j].getNome()) > 0) 
                        {
                            pokemon temp = arr[j];
                            arr[j] = arr[i];
                            arr[i] = temp;
                            mov++;
                        }
                    }
                }
            }
        }
    
        // Gravar o log no arquivo
        try (FileWriter fw = new FileWriter("844871_insercao.txt")) 
        {
            fw.write("844871\t" + comp + "\t" + mov + "\t" + logTime.getTime());
        } 
        catch (Exception e) 
        {
            e.printStackTrace();
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

    public static pokemon learquivo(String caminho, int numero, pokemon generico)
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

                if (generico.id == numero) 
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

        //System.out.println("Digita seu numero ai vai: ");
        String numero = sc.nextLine();

        pokemon poke[] = new pokemon[100];
        for (int i = 0; i < poke.length; i++) {poke[i] = new pokemon();}

        int cont = 0;

        while (numero.equals("FIM") == false)
        {
            //String caminho = "/Users/mateusmac/Projects/AEDS_2/Tp2/pokemon.csv";
            String caminho = "/tmp/pokemon.csv";
    
            poke[cont] = learquivo(caminho, Integer.parseInt(numero), poke[cont]);
            
            cont++;

            //System.out.println("Digita seu numero ai vai: ");
            numero = sc.nextLine();
        }

        ordenacao(poke, cont);

        for(int i = 0; i<poke.length;  i++)
        {
            if(poke[i].id != 0)
            {
                System.out.println(Stringpronta(poke[i]));
            }
        }
        
        sc.close();
    }
}
