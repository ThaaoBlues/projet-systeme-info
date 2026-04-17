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

    process(ADDR_A,ADDR_B,ADDR_W,W,DATA,CLK,RST)
    begin


        -- front montant
        if rising_edge(CLK) then
            -- reset synchrone
            if RST = '0' then
                regs  <= (others => (others => '0'));
                QA   <= (others => '0');
                QB   <= (others => '0');
            else
                if W = '0' then
                    -- lecture d'un registre
                    if unsigned(ADDR_A) /= 0 then
                        QA <= regs(to_integer(unsigned(ADDR_A)));
                        
                    end if;

                    -- possibilité de lire un second registre en même temps
                    if unsigned(ADDR_B) /= 0 then
                        QB <= regs(to_integer(unsigned(ADDR_B)));
                        
                    end if;

                else
                    -- écriture d'un registre
                    regs(to_integer(unsigned(ADDR_W))) <= DATA;

                    -- BYPASS
                    if ADDR_A = ADDR_W then
                        QA <= DATA;
                    elsif ADDR_B = ADDR_W then
                        QB <= DATA;
                    end if;

                end if;

            end if;
        end if;

    end process;

end architecture;
