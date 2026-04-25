----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/17/2026 02:37:24 PM
-- Design Name: 
-- Module Name: DATA_MEM - Behavioral
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

entity DATA_MEM is
    PORT (
        ADDR : in std_logic_vector( 7 downto 0);
        ENTREE : in std_logic_vector(31 downto 0);
        RW : in std_logic;
        RST : in std_logic;
        CLK : in std_logic;
        SORTIE : out std_logic_vector(31 downto 0)
    );
end DATA_MEM;

architecture Behavioral of DATA_MEM is


    type mem is array(255 downto 0) of std_logic_vector(31 downto 0);
    signal data : mem := (others => (others => '0'));
begin
    
    process(CLK)
    
    begin
    
        if CLK'Event and CLK = '1' then
            if RST = '1' then
                data <= (others => (others => '0'));
                SORTIE <= (others => '0');
            elsif RW = '1' then 
            
                SORTIE <= data(to_integer(unsigned(ADDR)));

            elsif RW = '0' then
                data(to_integer(unsigned(ADDR))) <= ENTREE;
            end if;
        
        end if;
    
    
    end process;

end Behavioral;

