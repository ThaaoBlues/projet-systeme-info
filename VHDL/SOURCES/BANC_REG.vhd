library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity BANC is

    port(
        ADDR_A : in std_logic_vector(3 downto 0);
        ADDR_B : in std_logic_vector(3 downto 0);
        ADDR_W : in std_logic_vector(3 downto 0);
        W : in std_logic;
        DATA : in std_logic_vector(7 downto 0);
        RST : in std_logic;
        CLK : in std_logic;
        QA : out std_logic_vector(7 downto 0);
        QB : out std_logic_vector(7 downto 0)

    );

end BANC;



architecture beh of BANC is
     type banc_reg is array (0 to 15) of std_logic_vector(7 downto 0);
     signal regs : banc_reg := (others => (others => '0'));
begin 

    process(CLK,RST)
    begin


        if CLK'Event and CLK = '1' then
            -- reset synchrone
            if RST = '0' then
                regs  <= (others => (others => '0'));
            elsif W = '1' then
                    -- écriture d'un registre
                    regs(to_integer(unsigned(ADDR_W))) <= DATA;
            end if;
        end if;

    end process;
    
    
    -- prend en compte le bypass
    QA <= DATA when (W = '1' and ADDR_A = ADDR_W) else 
              regs(to_integer(unsigned(ADDR_A)));
          
    QB <= DATA when (W = '1' and ADDR_B = ADDR_W) else 
          regs(to_integer(unsigned(ADDR_B)));

end architecture;
