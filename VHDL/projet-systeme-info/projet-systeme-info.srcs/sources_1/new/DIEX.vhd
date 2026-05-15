----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/04/2026 01:13:24 PM
-- Design Name: 
-- Module Name: DIEX - Behavioral
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

entity DIEX is
    
    Port (CLK : in std_logic;  
    OP_IN, A_IN, B_IN, C_IN : in STD_LOGIC_VECTOR (7 downto 0);
            OP_OUT, A_OUT, B_OUT, C_OUT : out STD_LOGIC_VECTOR (7 downto 0));
end DIEX;

architecture beh of DIEX is

begin
      process(CLK) begin
        if rising_edge(CLK) then
            
            OP_OUT <= OP_IN; A_OUT <= A_IN; B_OUT <= B_IN; C_OUT <= C_IN;
        end if;
        
      end process;


end beh;
