----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 05/11/2026 12:56:27 PM
-- Design Name: 
-- Module Name: lc_re - Behavioral
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

entity lc_re is
    port( op : in std_logic_vector (7 downto 0);
        w_out : out std_logic);

end lc_re;

architecture Behavioral of lc_re is

    signal op_cool : std_logic;
begin
-- Toute les instruction demandant d'écrire sur le banc de registre sont de la forme 0x8X. Donc le bit de poid fort est à un. On a donc simplement
-- besoin de regardé le 7e bit de op.
    op_cool <= op(7);
    
    w_out <= op_cool when op_cool='1' else "0";
       
        
end Behavioral;
