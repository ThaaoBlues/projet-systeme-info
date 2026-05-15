----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/10/2026 01:00:40 PM
-- Design Name: 
-- Module Name: ALU - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;


entity ALU is
    Port(
        CLK : in std_logic; --clk pour copier les registre dans les registre interne de l'ALU
        B,A : in std_logic_vector(7 downto 0);
        S : out std_logic_vector(7 downto 0);
        
        Ctrl_ALU : in std_logic_vector(2 downto 0);
        Carry,Overflow,Negatif,Zero : out std_logic
    );

    
end ALU;

architecture beh of ALU is
    -- registre de l'ALU
    signal r1_res       : std_logic_vector(15 downto 0) := (others => '0');
    signal r1_Ctrl : std_logic_vector(2 downto 0);
    
begin
    

    process (Clk)
        variable res : std_logic_vector(15 downto 0) := (others => '0');
        variable resize_A : std_logic_vector(15 downto 0) := (others => '0');
        variable resize_B : std_logic_vector(15 downto 0) := (others => '0');
    begin
        if rising_edge(clk) then
            r1_Ctrl <= Ctrl_ALU;
            -- Initialisation par défaut pour éviter les Latches

            resize_A := std_logic_vector(resize(signed(A),16));
            resize_B := std_logic_vector(resize(signed(B),16));
    
    
            case Ctrl_ALU is
                when "001" => --Add
                    res := std_logic_vector(signed(resize_A) + signed(resize_B));
                    
                    
                when "011" => --sub
                    res := std_logic_vector(signed(resize_A) - signed(resize_B));
                    
                    
                when "010" => --mul
                    res := std_logic_vector(signed(A) * signed(B));
                          
                when "100" => -- div
                    res := std_logic_vector(signed(resize_A) / signed(resize_B));
                when "101" => --and
                    res(7 downto 0) := A AND B;
                when "110" => --or
                    res(7 downto 0) := A OR B;
                when "111" => -- xor
                    res(7 downto 0) := A XOR B;
                when others =>
                    res := (others => 'U');
                end case;
                r1_res <= res;
           end if;
       end process;
       
       -- Etage 2 (calcul flags)--
       
       process(clk)
       begin
       


            if rising_edge(clk) then
                Zero <= '0';
                Negatif  <= '0';
                S <= (others => '0');
                Carry <= '0';
                Overflow <= '0';
                
                
                
                 if (signed(r1_res) > 127 or signed(r1_res) < -128) and ( r1_Ctrl = "001" or r1_Ctrl = "011") then 
                        Carry <= '1'; 
                 elsif (signed(r1_res) > 127 or signed(r1_res) < -128) and ( r1_Ctrl = "010") then
                    Overflow <= '1';
                 end if;
                 
                 
                S <= r1_res(7 downto 0);
                
                
                if (signed(r1_res) = 0) then
                    Zero <=  '1';
                 else 
                    Zero <= '0';
                end if;
                
                if(signed(r1_res) < 0) then
                    Negatif <= '1';
                else
                    Negatif <= '0';
                    
                end if;
                    
                
            end if;
       end process;
 
    
end beh;
