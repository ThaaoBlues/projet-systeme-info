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
        B,A : in std_logic_vector(7 downto 0);
        S : out std_logic_vector(7 downto 0);
        Cadd,Csub,Cmul,Cxor,Cand,Cor,Cnot,Cdiv : in std_logic;
        Carry,Overflow,Negatif,Zero : out std_logic
    );

    
end ALU;

architecture Behavioral of ALU is



begin
    process (A, B, Cadd, Csub, Cmul, Cdiv, Cxor, Cand, Cor, Cnot)
        variable res : std_logic_vector(15 downto 0) := (others => '0');
        variable resize_A : std_logic_vector(15 downto 0) := (others => '0');
        variable resize_B : std_logic_vector(15 downto 0) := (others => '0');
    begin
        -- Initialisation par défaut pour éviter les Latches
        Carry    <= '0';
        Zero     <= '0';
        Negatif  <= '0';
        Overflow <= '0';
        S        <= (others => '0');

        resize_A := std_logic_vector(resize(signed(A),16));
        resize_B := std_logic_vector(resize(signed(B),16));

        if Cadd = '1' then
            res := std_logic_vector(signed(resize_A) + signed(resize_B));
            
            
            if (signed(res) < -128 ) then
                Carry <=  '1';
             else 
                Carry <= '0';
             end if;
             
            
        elsif Csub = '1' then
            res := std_logic_vector(signed(resize_A) - signed(resize_B));

            if (signed(res) < -128) then
                Carry <=  '1';
             else 
                Carry <= '0';
             end if;
             
           

            
        elsif Cmul = '1' then
            res := std_logic_vector(signed(A) * signed(B));

            if (signed(res) > 127) then
            
                Overflow <= '1';
            else
                Overflow <= '0';
            end if;
           
             
        elsif Cdiv = '1' then
            res := std_logic_vector(signed(resize_A) / signed(resize_B));

        elsif Cxor = '1' then
            res(7 downto 0) := A xor B; 
        elsif Cand = '1' then
            res(7 downto 0) := A AND B;
        elsif Cor = '1' then
            res(7 downto 0) := A OR B;
        elsif Cnot = '1' then
            res(7 downto 0) := std_logic_vector(NOT A);
        end if;
        if (signed(res) = 0) then
            Zero <=  '1';
         else 
            Zero <= '0';
         end if;
            
             
        S <= res(7 downto 0);
    end process;
    
end Behavioral;
