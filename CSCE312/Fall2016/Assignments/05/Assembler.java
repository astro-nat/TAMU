import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;
import java.text.NumberFormat;
import java.text.ParsePosition;
import java.util.Map;
import java.util.TreeMap;
import java.io.File;
import java.io.FileWriter;
import java.io.BufferedWriter;

class SymbolTable {
	private static Map<String, String> symbol_table;
	
	public SymbolTable() {
		 symbol_table = new TreeMap<String,String>();
		  
		 	symbol_table.put("SP", "0");
			symbol_table.put("LCL", "1");
			symbol_table.put("ARG", "2");
			symbol_table.put("THIS", "3");
			symbol_table.put("THAT", "4");
			symbol_table.put("R0", "0");
			symbol_table.put("R1", "1");
			symbol_table.put("R2", "2");
			symbol_table.put("R3", "3");
			symbol_table.put("R4", "4");
			symbol_table.put("R5", "5");
			symbol_table.put("R6", "6");
			symbol_table.put("R7", "7");
			symbol_table.put("R8", "8");
			symbol_table.put("R9", "9");
			symbol_table.put("R10", "10");
			symbol_table.put("R11", "11");
			symbol_table.put("R12", "12");
			symbol_table.put("R13", "13");
			symbol_table.put("R14", "14");
			symbol_table.put("R15", "15");
			symbol_table.put("SCREEN", "16384");
			symbol_table.put("KBD", "24576");
	}
	
	public void addEntry(String key, String value) {
		symbol_table.put(key, value);	
	}
	
	
	public boolean containKey(String key){
		return symbol_table.containsKey(key);
	}
	
	public String getValue(String val)
	{
		return	symbol_table.get(val);	
	}
	
}

class Code {
	//jump table
	private Map<String, String> jump;
	//comp table
	private Map<String, String> comp;
	//dest table
	private Map<String, String> dest;
	
	
	public Code()
	{
		
		jump = new TreeMap<String,String>();
		jump.put("NULL", "000");
		jump.put("JGT", "001");
		jump.put("JEQ", "010");
		jump.put("JGE", "011");
		jump.put("JLT","100");
		jump.put("JNE","101");
		jump.put("JLE","110");
		jump.put("JMP", "111");
		
		
		comp = new TreeMap<String,String>();
		comp.put("0", "0101010");
		comp.put("1", "0111111");
		comp.put("-1","0111010");
		comp.put("D", "0001100");
		comp.put("A", "0110000");
		comp.put("!D", "0001101");
		comp.put("!A", "0110001");
		comp.put("-D", "0001111");
		comp.put("-A", "0110011");
		comp.put("D+1","0011111");
		comp.put("A+1","0110111");
		comp.put("D+A","0000010");
		comp.put("D-A","0010011");
		comp.put("A-D","0000111");
		comp.put("D&A","0000000");
		comp.put("D|A","0010101");	
		comp.put("M","1110000");
		comp.put("!M","1110001");
		comp.put("-M","1110011");
		comp.put("M+1","1110111");
		comp.put("M-1","1110010");
		comp.put("D+M","1000010");
		comp.put("D-M","1010011");
		comp.put("M-D","1000111");
		comp.put("D&M","1000000");
		comp.put("D|M","1010101");
		comp.put("D-1","0001110");
		comp.put("A-1","0110010");

		
		dest = new TreeMap<String, String>();
		dest.put("NULL","000");
		dest.put("M","001");
		dest.put("D","010");
		dest.put("MD","011");
		dest.put("A","100");
		dest.put("AM","101");
		dest.put("AD","110");
		dest.put("AMD","111");		
		
	}
	
	public String getDest(String mneumonic)
	{
		return dest.get(mneumonic);
	}
	
	public String getComp(String mneumonic)
	{
		return comp.get(mneumonic);
	}
	
	
	public String getJump(String mneumonic)
	{
		return jump.get(mneumonic);
	}

}

class Parser {
	private  String str_input; 
	public  String str_input_array[]; 
	public static String current;
	public int counter; 
	public BufferedReader br;
	public static commandType comType; 
	
	
	Parser(String filename)
	{
		counter = 0;
		
		FileInputStream fstream = null; 
		try {
			fstream = new FileInputStream(filename);
		} catch (FileNotFoundException e1) {
			e1.printStackTrace();
		}
	
		int store;
        try {
			while ((store = fstream.read()) != -1) {
			    str_input += (char) store; 	
			}
		} catch (IOException e) {
			e.printStackTrace();
		}
         
        
		    DataInputStream in = new DataInputStream(fstream);
		    br = new BufferedReader(new InputStreamReader(in));
		    
		    
		   str_input =  removeComments(str_input);
		   
		   str_input_array = str_input.split("\n");
		   //trim
		   for(int i=0; i < str_input_array.length; i++){
			   str_input_array[i] =  str_input_array[i].trim();
       }
		   
	}
	
	
	public boolean hasMoreCommand() {
		if(counter != str_input_array.length) return true;
		return false;
		
	}
	
	
	public  void advance()
	{
		counter++;
	}
	
	public commandType commandType()
	{
		if(str_input_array[counter].startsWith("("))
		{
			return comType = commandType.L_COMMAND;
		}
		else if(str_input_array[counter].startsWith("@"))
		{
			return comType = commandType.A_COMMAND;
		}
		return commandType.C_COMMAND;
	}
	
	
	public String symbol()
	{
		String lable = "";
		if(str_input_array[counter].startsWith("@"))
		{
			lable = str_input_array[counter];
			lable = lable.replaceAll("@", "");
		}
		else 
			if(str_input_array[counter].startsWith("("))
			{
				lable = str_input_array[counter];
				lable = lable.replaceAll("\\((.*?)\\)", "$1");
			}
		return lable;
	}
	
	//dest
	public String dest() {
		if(str_input_array[counter].contains("="))
		{
		String temp_dest = str_input_array[counter];
		
		int endIndex = temp_dest.lastIndexOf("=");
		temp_dest =  temp_dest.substring(0,endIndex);
		return temp_dest;
		}
		return null;
	}
	
	public String comp() {
		String temp_comp = str_input_array[counter]; 
		if(str_input_array[counter].contains("="))
		{
		int endIndex = temp_comp.lastIndexOf("=");
		temp_comp =  temp_comp.substring(endIndex+1,temp_comp.length());
		}
		else if(str_input_array[counter].contains(";"))
		{
			
			int endIndex = temp_comp.lastIndexOf(";");
			temp_comp =  temp_comp.substring(0,endIndex);
		}
		return temp_comp;
		
	}

	public String jump() {
		if(str_input_array[counter].contains(";"))
		{
			String retJump = str_input_array[counter]; 
			int endIndex = retJump.lastIndexOf(";");
			return retJump.substring(endIndex+1,retJump.length());
		}
		return null;
		
	}
	
	
	public String removeComments(String file) {
		String temp =  file.replaceAll( "//.*|(\"(?:\\\\[^\"]|\\\\\"|.)*?\")|(?s)/\\*.*?\\*/|(?m)^[ \t]*\r?\n|null|\t", "" );
		temp = temp.replaceAll("(?m)^[ \t]*\r?\n", "");
        return temp;
	}
	

	public enum commandType
	{
		A_COMMAND,L_COMMAND,C_COMMAND
	}
	
	//dec to bin converter
	public static String dexToBin(int value) {
	String binVal = Integer.toBinaryString(value);
		return binVal;
		
	}
	//check's if number
	public boolean isNum(String num)
	{
		NumberFormat formatter = NumberFormat.getInstance();
		  ParsePosition pos = new ParsePosition(0);
		  formatter.parse(num, pos);
		  return  num.length() == pos.getIndex();
		
	}
	
	//adds zeroes
	public String addZero(String num)
	{
		StringBuilder sb = new StringBuilder();

		for (int toPrepend=16-num.length(); toPrepend>0; toPrepend--) {
		    sb.append('0');
		}

		sb.append(num);
		String result = sb.toString();
		return result;
	}

	}

public class Assembler {
	public static  int counter=0;
	public static int nextRam = 16;
	public static String compT,destT,jumpT; 
	public static void main(String[] args) {
	
	
		
		String name = args[0].substring(0, args[0].indexOf('.'));	
		
		String outFileName = name+".hack"; 
		
		SymbolTable st = new SymbolTable(); 
		
		Code ct = new Code();  
		
		Parser newParser = new Parser(args[0]);  
	
		File out = new File(outFileName); 
		
		FileWriter fw = null;
		try {
			fw = new FileWriter(out.getAbsoluteFile());
		} catch (IOException e) {
			e.printStackTrace();
		}
		BufferedWriter bw = new BufferedWriter(fw);
	
		
		while(newParser.hasMoreCommand()) {  
		if(newParser.commandType()== Parser.commandType.L_COMMAND) { 
			
			st.addEntry(newParser.symbol(),Integer.toString(counter)) ; 
		}
		else counter++; 
		
		newParser.advance(); 
		
		}
		newParser.counter =0;  
		
		
		while(newParser.hasMoreCommand())
		{
			if(newParser.commandType()== Parser.commandType.A_COMMAND) 
			{
				if(newParser.str_input_array[newParser.counter].startsWith("@"))
				{
				String tmp  = newParser.symbol(); 
					if(newParser.isNum(tmp)) 
					{
						int xxx = Integer.parseInt(tmp);
						tmp = Parser.dexToBin(xxx);
						tmp = newParser.addZero(tmp);
						try {
							bw.write(tmp + '\n');
						} catch (IOException e) {
							e.printStackTrace();
						}
						
					}
					else 
					{
						if(!st.containKey(tmp))  
						{
							st.addEntry(tmp,Integer.toString(nextRam));  
							nextRam++;
						}
						 if(st.containKey(tmp)) 
							{
							String tmp2 = st.getValue(tmp);
							int xxx = Integer.parseInt(tmp2);
							tmp2 = Parser.dexToBin(xxx);
							tmp2 = newParser.addZero(tmp2);
							try {
								bw.write(tmp2+'\n'); 
							} catch (IOException e) {
								e.printStackTrace();
							}
						}
					}
				}
			}
			if(newParser.commandType()== Parser.commandType.C_COMMAND)
			{
				if(newParser.str_input_array[newParser.counter].contains("="))
				{
					
					
					destT = ct.getDest(newParser.dest());
					compT = ct.getComp(newParser.comp());
					jumpT = ct.getJump("NULL");  
					try {
						bw.write("111" + compT + destT + jumpT +'\n');
					} catch (IOException e) {
						e.printStackTrace();
					}
					
				}
				else if(newParser.str_input_array[newParser.counter].contains(";")) 
				{
					destT = ct.getDest("NULL"); 
					compT = ct.getComp(newParser.comp());
					jumpT = ct.getJump(newParser.jump());
					
					try {
						bw.write("111" + compT + destT + jumpT +'\n');
					} catch (IOException e) {
						e.printStackTrace();
					}
				}
			}
			newParser.advance();		
		}
		
try {
	bw.close();
} catch (IOException e) {
	e.printStackTrace();
}
}

}