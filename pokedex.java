import java.io.File;
//import java.nio.file.Paths;
import java.util.Scanner;


public class pokedex 
{
    public static String learquivo(String caminho, int numero)
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

                int id = Integer.parseInt(partes[0]);
                String nome = partes[2];
                String descripiton = partes[3];
                String types1 = partes[4];
                String types2 = null;
                if(partes[5].isEmpty())
                {
                    types2 = "']";
                }
                else
                {
                    types2 = "', '"+partes[5]+"']";
                }
               
                String habilidades = habilidade2[0];
                double peso;
                if(partes2[1].isEmpty())
                {
                    peso = 0;
                }
                else
                {
                    peso = Double.parseDouble(partes2[1]);
                }
                double altura;
                if(partes2[2].isEmpty())
                {
                    altura = 0;
                }
                else
                {
                    altura = Double.parseDouble(partes2[2]);
                }
                int raridade = Integer.parseInt(partes2[3]);
                int isLegendary = Integer.parseInt(partes2[4]);
                String data = partes2[5];


                if (id == numero) 
                {
                    condicao = true;
                    
                    StringBuilder pronta = new StringBuilder();
                    pronta.append("[#").append(id)
                        .append(" -> ").append(nome)
                        .append(": ").append(descripiton)
                        .append(" - ['").append(types1);

                    pronta.append(types2);
                    

                    pronta.append(" - [").append(habilidades); 

                    pronta.append("] - ").append(peso).append("kg") 
                        .append(" - ").append(altura).append("m") 
                        .append(" - ").append(raridade).append("%");
                        if(isLegendary == 0)
                        {
                            pronta.append(" - ").append("false");
                        }
                        else
                        {
                            pronta.append(" - ").append("true");
                        }
                    pronta.append(" - ").append(partes[1]).append(" gen] - ") 
                        .append(data); 

                    String resultado = pronta.toString();
                    
                    sc.close();

                    return resultado;
                }
                
            }
            sc.close();

        } 
        catch (Exception e) 
        {
            System.out.println("Deu merda ai meu patrao: " + e.getMessage());
        }

        sc.close();
        
        return "";
    }

    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        //System.out.println("Digita seu numero ai vai: ");
        String numero = sc.nextLine();

        while (numero.equals("FIM") == false) 
        {
            //String caminho = "/Users/mateusmac/Projects/AEDS_2/Tp2/pokemon.csv";
            String caminho = "/tmp/pokemon.csv";
    
            System.out.println(learquivo(caminho, Integer.parseInt(numero)));

            //System.out.println("Digita seu numero ai vai: ");
            numero = sc.nextLine();
        }

        sc.close();
    }
}
