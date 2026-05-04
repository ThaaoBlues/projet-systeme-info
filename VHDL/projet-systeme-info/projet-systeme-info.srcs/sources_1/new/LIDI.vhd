----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/04/2026 01:04:17 PM
-- Design Name: 
-- Module Name: LIDI - Behavioral
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

entity LIDI is
     Port ( 
        CLK  : in std_logic;
        INST : in std_logic_vector(31 downto 0);
        OP,A,B,C   : out std_logic_vector(7 downto 0)
     );
end LIDI;

architecture beh of LIDI is

begin
    process(CLK)
    
    begin
    
        if CLK'Event and CLK = '1' then
            A <= INST(7 downto 0);
            OP <= INST(15 downto 8);
            B <= INST(23 downto 16);
            C <= INST(31 downto 24);
         end if;
    end process;
         



end beh;
