----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 04/25/2026 12:53:11 PM
-- Design Name: 
-- Module Name: pipeline - Structural
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

entity pipeline is
--  Port ( );
end pipeline;

architecture Structural of pipeline is

component ROM port(
        ADDR : in std_logic_vector( 7 downto 0);
        CLK : in std_logic;
        SORTIE : out std_logic_vector(31 downto 0)
);
end component;


-- TODO DANS VIVADO : créer le composant clock
component CLOCK port(
    CLK : out std_logic
);
end component;

-- TODO DANS VIVADO : créer le composant LI/DI
-- il s'agit juste d'un truc qui split les 4 octets
-- et les mets chacun dans son registre
component LIDI port(
        CLK  : in std_logic;
        INST : in std_logic_vector(31 downto 0);
        OP,A,B,C   : out std_logic_vector(7 downto 0)
    );
end component;


component BANC_REG port(
        ADDR_A,ADDR_B,ADDR_W : in std_logic_vector(3 downto 0);
        W      : in std_logic;
        DATA   : in std_logic_vector(7 downto 0);
        RST    : in std_logic;
        CLK    : in std_logic;
        QA,QB  : out std_logic_vector(7 downto 0)
    
    );
end component;


-- TODO : composant à faire
-- je pense que là c'est juste 4 registres
component DIEX port(
        CLK: in std_logic;
        OP_IN, A_IN, B_IN, C_IN: in std_logic_vector(7 downto 0);
        OP_OUT, A_OUT, B_OUT, C_OUT: out std_logic_vector(7 downto 0)
    );
end component;

-- TODO : composant à faire
-- je pense que là c'est juste 4 registres
component EXMEM port(
        CLK: in std_logic; 
        OP_IN, A_IN, B_IN: in std_logic_vector(7 downto 0);
        OP_OUT, A_OUT, B_OUT: out std_logic_vector(7 downto 0)
    );
end component;

-- TODO : composant à faire
-- là jsp c'est un peu plus complexe comme il touche au banc de registres
component MEMRE port(
        CLK: in std_logic; 
        OP_IN, A_IN, B_IN: in std_logic_vector(7 downto 0);
        OP_OUT, A_OUT, B_OUT: out std_logic_vector(7 downto 0)
    );
end component;


component ALU
    Port(
        B, A : in  std_logic_vector(7 downto 0);
        S : out std_logic_vector(7 downto 0);
        Cadd, Csub, Cmul, Cxor, Cand, Cor, Cnot, Cdiv : in std_logic;
        Carry, Overflow, Negatif, Zero : out std_logic
    );
end component;



component DATA_MEM
    PORT (
        ADDR   : in std_logic_vector(7 downto 0);
        ENTREE : in std_logic_vector( 31 downto 0);
        RW     : in std_logic;
        RST    : in std_logic;
        CLK    : in std_logic;
        SORTIE : out std_logic_vector(31 downto 0)
    );
end component;


signal ip : std_logic_vector(7 downto 0) := (others => '0');
signal clock : std_logic := '0';

-- sortie ROM
signal inst_4o : std_logic_vector(31 downto 0) := (others => '0');

-- sortie LI/DI
signal op_li_di, a_li_di, b_li_di, c_li_di : std_logic_vector(7 downto 0);

-- sortie banc de registres principaux (on utilise pas pour afc encore)
signal qa_out, qb_out : std_logic_vector(7 downto 0);

-- sortie DI/EX
signal op_di, a_di, b_di, c_di : std_logic_vector(7 downto 0);

-- sortie EX/MEM
signal op_ex, a_ex, b_ex : std_logic_vector(7 downto 0);

-- sortie MEM/RE
signal op_re, a_re, b_re : std_logic_vector(7 downto 0);


-- sortie ALU
signal alu_out : std_logic_vector(7 downto 0);

-- sortie memoire donnees
signal data_mem_out : str

begin

    clock_component : CLOCK port map(clock); 
-- LES MULTIPLEXERS SERONT DES COMPOSANTS   
    mem_code : ROM port map(ADDR<=ip,CLK<=clock,SORTIE<=inst_4o);
    
    
-- LI/DI
    li_di : LIDI port map(INST<=inst_4o,OP<=op_li_di,A<=a_li_di,B<=b_li_di,C<=c_li_di);


    banc_registres_principal : BANC_REG port map(
        ADDR_A => b_li_di(3 downto 0),
        ADDR_B => c_li_di(3 downto 0),
        ADDR_W => "0000", -- TODO: à relier à la sortie a_re
        W      => '0',    -- TODO : à relier au controleur en fonction de op_re
        DATA   => x"00",  -- TODO : à relier à la sortie b_re
        RST    => rst,
        CLK    => clock,
        QA     => qa_out,
        QB     => qb_out
    );


-- ATTENTION : les sorties LI/DI sont branchées sur di_ex
-- mais on va devoir bancher le banc de registres entre les deux
-- donc il va falloir séparer sortie li_di et signaux en entrée de DIEX 
-- on va donc mettre des mux partout presque
-- ce sera la même pour tous les étages

-- DI/EX
    alu : alu port map(A => b_di,
                       B => c_di,
                       OP => op_di, -- TODO : passer par le controleur avant ici (jsp pq)
                       S => alu_out
                    );


    di_ex : DIEX port map(CLK => clock,
                                OP_IN => op_li_di, 
                                A_IN => a_li_di, 
                                B_IN => b_li_di, -- TODO : mux entre b_li_di,qa_out suivant op_li_di
                                C_IN => c_li_di, -- TODO : relier directement à qb du banc de registre
                                OP_OUT => op_di, 
                                A_OUT => a_di, 
                                B_OUT => b_di, 
                                C_OUT => c_di
                            );

-- EX/MEM

    ex_mem : EXMEM port map(CLK => clock,
                                OP_IN => op_di, 
                                A_IN => a_di,
                                B_IN => b_di, -- TODO: mux entre sortie d'ALU, b_di suivant op_di
                                OP_OUT => op_ex, 
                                A_OUT => a_ex, 
                                B_OUT => b_ex
                            );

-- MEM/RE

    data_mem : DATA_MEM port map(ADDR => a_ex, -- TODO : mux entre b_ex, a_ex en fonction de op_ex
                                 IN_DATA => b_ex, 
                                 RW => '1', --TODO : c'est le controleur, en fonction de op_ex
                                 CLK => clock, 
                                 OUT_DATA => data_mem_out
                                );


    mem_re : MEMRE port map(CLK => clock, 
                            OP_IN => op_ex, 
                            A_IN => a_ex, 
                            B_IN => b_ex, -- TODO : mux entre b_ex,data_mem_out suivant op_ex 
                            OP_OUT => op_re, 
                            A_OUT => a_re, 
                            B_OUT => b_re
                        );

-- process d'incrémentation de IP
    process(clock) begin
        if clock'Event AND clock='1' then 
            ip <= ip + 1; 
        end if;
    end process;


end Structural;



-- LES REGISTRES DE PIPELINE VONT RESSEMBLER A CA
-- SAUF LE PREMIER ET DERNIER YA DES TRUCS EN PLUS PEUT-ETRE
-- entity DIEX is
--     Port ( CLK : in STD_LOGIC;
--            OP_IN, A_IN, B_IN, C_IN : in STD_LOGIC_VECTOR (7 downto 0);
--            OP_OUT, A_OUT, B_OUT, C_OUT : out STD_LOGIC_VECTOR (7 downto 0));
-- end DIEX;

-- architecture Behavioral of DIEX is
-- begin
--     process(CLK) begin
--         if rising_edge(CLK) then
--             OP_OUT <= OP_IN; A_OUT <= A_IN; B_OUT <= B_IN; C_OUT <= C_IN;
--         end if;
--     end process;
-- end Behavioral;