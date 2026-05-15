----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/15/2026 03:05:43 PM
-- Design Name: 
-- Module Name: EX1EX2 - Behavioral
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



--cette entité permet de créer un décalage de 1 clock pour que l'alu ai le temps de finir son calcul.
entity EX1EX2 is
    Port(
        CLK                    : in  std_logic;
        OP_IN, A_IN, B_IN      : in  std_logic_vector(7 downto 0);
        OP_OUT, A_OUT, B_OUT   : out std_logic_vector(7 downto 0)
    );
end EX1EX2;

architecture beh of EX1EX2 is

begin
    process(CLK) begin
        if rising_edge(CLK) then
            OP_OUT <= OP_IN;
            A_OUT  <= A_IN;
            B_OUT  <= B_IN;
        end if;
    end process;

end beh;
