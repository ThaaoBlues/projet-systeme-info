----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/15/2026 04:19:50 PM
-- Design Name: 
-- Module Name: retard_B_alu - Behavioral
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
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity retard_B_alu is
     Port ( 
            Clk : in std_logic;
            B : in std_logic_vector(7 downto 0);
            B_out : out std_logic_vector(7 downto 0) );
end retard_B_alu;

architecture Behavioral of retard_B_alu is
    signal b_r1 : std_logic_vector(7 downto 0);
begin
    process(Clk)
    begin
        if rising_edge(Clk) then
            b_r1  <= B;      -- cycle N+1
            B_out <= b_r1;   -- cycle N+2
        end if;
    end process;
end Behavioral;
