----------------------------------------------------------------------------------
-- Testbench pour ALU 8 bits
-- Teste : ADD, SUB, MUL, DIV, XOR, AND, OR, NOT
-- Vérifie : S, Carry, Overflow, Zero, Negatif
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity ALU_tb is
end ALU_tb;

architecture Behavioral of ALU_tb is

    ------------------------------------------------------------
    -- Composant sous test
    ------------------------------------------------------------
    component ALU
        Port(
            B, A     : in  std_logic_vector(7 downto 0);
            S        : out std_logic_vector(7 downto 0);
            Cadd, Csub, Cmul, Cxor, Cand, Cor, Cnot, Cdiv : in std_logic;
            Carry, Overflow, Negatif, Zero : out std_logic
        );
    end component;

    ------------------------------------------------------------
    -- Signaux de stimulation
    ------------------------------------------------------------
    signal A, B      : std_logic_vector(7 downto 0) := (others => '0');
    signal S         : std_logic_vector(7 downto 0);
    signal Cadd, Csub, Cmul, Cxor, Cand, Cor, Cnot, Cdiv : std_logic := '0';
    signal Carry, Overflow, Negatif, Zero : std_logic;

    ------------------------------------------------------------
    -- Constante de délai entre chaque test
    ------------------------------------------------------------
    constant T : time := 20 ns;

    ------------------------------------------------------------
    -- Procédure utilitaire : réinitialise toutes les commandes
    ------------------------------------------------------------
    procedure reset_cmds(
        signal Cadd, Csub, Cmul, Cdiv,
               Cxor, Cand, Cor, Cnot : out std_logic) is
    begin
        Cadd <= '0'; Csub <= '0'; Cmul <= '0'; Cdiv <= '0';
        Cxor <= '0'; Cand <= '0'; Cor  <= '0'; Cnot <= '0';
    end procedure;

begin

    ------------------------------------------------------------
    -- Instanciation du DUT
    ------------------------------------------------------------
    DUT : ALU
        port map (
            A => A, B => B, S => S,
            Cadd => Cadd, Csub => Csub, Cmul => Cmul, Cdiv => Cdiv,
            Cxor => Cxor, Cand => Cand, Cor  => Cor,  Cnot => Cnot,
            Carry => Carry, Overflow => Overflow,
            Negatif => Negatif, Zero => Zero
        );

    stim : process
    begin
        report "========== DEBUT DES TESTS ALU ==========";

        -- ====================================================
        -- 1. ADDITION : cas normal  3 + 4 = 7
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= std_logic_vector(to_signed(3, 8));
        B <= std_logic_vector(to_signed(4, 8));
        Cadd <= '1';
        wait for T;
        assert S = std_logic_vector(to_signed(7, 8))
            report "ECHEC ADD 3+4 : S=" & integer'image(to_integer(signed(S))) severity error;
        assert Carry = '0'
            report "ECHEC ADD 3+4 : Carry attendu 0" severity error;
        assert Zero = '0'
            report "ECHEC ADD 3+4 : Zero attendu 0" severity error;
        report "ADD  3 + 4 = " & integer'image(to_integer(signed(S))) &
               "  Carry=" & std_logic'image(Carry) &
               "  Zero="  & std_logic'image(Zero);

        -- ====================================================
        -- 2. ADDITION : débordement  100 + 100 = 200 > 127 → Carry
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= std_logic_vector(to_signed(100, 8));
        B <= std_logic_vector(to_signed(100, 8));
        Cadd <= '1';
        wait for T;
        assert Carry = '1'
            report "ECHEC ADD 100+100 : Carry attendu 1" severity error;
        report "ADD  100 + 100 = " & integer'image(to_integer(signed(S))) &
               "  Carry=" & std_logic'image(Carry);

        -- ====================================================
        -- 3. ADDITION : résultat zéro  0 + 0 = 0 → Zero
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= (others => '0');
        B <= (others => '0');
        Cadd <= '1';
        wait for T;
        assert Zero = '1'
            report "ECHEC ADD 0+0 : Zero attendu 1" severity error;
        report "ADD  0 + 0 = " & integer'image(to_integer(signed(S))) &
               "  Zero=" & std_logic'image(Zero);

        -- ====================================================
        -- 4. SOUSTRACTION : cas normal  10 - 3 = 7
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= std_logic_vector(to_signed(10, 8));
        B <= std_logic_vector(to_signed(3, 8));
        Csub <= '1';
        wait for T;
        assert S = std_logic_vector(to_signed(7, 8))
            report "ECHEC SUB 10-3" severity error;
        assert Carry = '0'
            report "ECHEC SUB 10-3 : Carry attendu 0" severity error;
        report "SUB  10 - 3 = " & integer'image(to_integer(signed(S))) &
               "  Carry=" & std_logic'image(Carry);

        -- ====================================================
        -- 5. SOUSTRACTION : résultat négatif  -50 - 100 = -150 → Carry
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= std_logic_vector(to_signed(-50, 8));
        B <= std_logic_vector(to_signed(100, 8));
        Csub <= '1';
        wait for T;
        assert Carry = '1'
            report "ECHEC SUB -50-100 : Carry attendu 1" severity error;
        report "SUB -50 - 100 = " & integer'image(to_integer(signed(S))) &
               "  Carry=" & std_logic'image(Carry);

        -- ====================================================
        -- 6. SOUSTRACTION : résultat zéro  5 - 5 = 0 → Zero
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= std_logic_vector(to_signed(5, 8));
        B <= std_logic_vector(to_signed(5, 8));
        Csub <= '1';
        wait for T;
        assert Zero = '1'
            report "ECHEC SUB 5-5 : Zero attendu 1" severity error;
        report "SUB  5 - 5 = " & integer'image(to_integer(signed(S))) &
               "  Zero=" & std_logic'image(Zero);

        -- ====================================================
        -- 7. MULTIPLICATION : cas normal  3 × 4 = 12
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= std_logic_vector(to_signed(3, 8));
        B <= std_logic_vector(to_signed(4, 8));
        Cmul <= '1';
        wait for T;
        assert S = std_logic_vector(to_signed(12, 8))
            report "ECHEC MUL 3x4" severity error;
        assert Overflow = '0'
            report "ECHEC MUL 3x4 : Overflow attendu 0" severity error;
        report "MUL  3 x 4 = " & integer'image(to_integer(signed(S))) &
               "  Overflow=" & std_logic'image(Overflow);

        -- ====================================================
        -- 8. MULTIPLICATION : débordement  20 × 20 = 400 > 127 → Overflow
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= std_logic_vector(to_signed(20, 8));
        B <= std_logic_vector(to_signed(20, 8));
        Cmul <= '1';
        wait for T;
        assert Overflow = '1'
            report "ECHEC MUL 20x20 : Overflow attendu 1" severity error;
        report "MUL  20 x 20 = " & integer'image(to_integer(signed(S))) &
               "  Overflow=" & std_logic'image(Overflow);

        -- ====================================================
        -- 9. DIVISION : cas normal  20 / 4 = 5
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= std_logic_vector(to_signed(20, 8));
        B <= std_logic_vector(to_signed(4, 8));
        Cdiv <= '1';
        wait for T;
        assert S = std_logic_vector(to_signed(5, 8))
            report "ECHEC DIV 20/4" severity error;
        report "DIV  20 / 4 = " & integer'image(to_integer(signed(S)));

        -- ====================================================
        -- 10. DIVISION : résultat zéro  0 / 5 = 0 → Zero
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= std_logic_vector(to_signed(0, 8));
        B <= std_logic_vector(to_signed(5, 8));
        Cdiv <= '1';
        wait for T;
        assert Zero = '1'
            report "ECHEC DIV 0/5 : Zero attendu 1" severity error;
        report "DIV  0 / 5 = " & integer'image(to_integer(signed(S))) &
               "  Zero=" & std_logic'image(Zero);

        -- ====================================================
        -- 11. XOR : 0xAA XOR 0x55 = 0xFF
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= x"AA";
        B <= x"55";
        Cxor <= '1';
        wait for T;
        assert S = x"FF"
            report "ECHEC XOR AA^55" severity error;
        report "XOR  0xAA ^ 0x55 = 0x" &
               integer'image(to_integer(unsigned(S)));

        -- ====================================================
        -- 12. XOR : résultat zéro  0xFF XOR 0xFF = 0x00 → Zero
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= x"FF";
        B <= x"FF";
        Cxor <= '1';
        wait for T;
        assert S = x"00"
            report "ECHEC XOR FF^FF" severity error;
        assert Zero = '1'
            report "ECHEC XOR FF^FF : Zero attendu 1" severity error;
        report "XOR  0xFF ^ 0xFF = 0x00  Zero=" & std_logic'image(Zero);

        -- ====================================================
        -- 13. AND : 0xF0 AND 0x0F = 0x00 → Zero
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= x"F0";
        B <= x"0F";
        Cand <= '1';
        wait for T;
        assert S = x"00"
            report "ECHEC AND F0&0F" severity error;
        assert Zero = '1'
            report "ECHEC AND F0&0F : Zero attendu 1" severity error;
        report "AND  0xF0 & 0x0F = 0x00  Zero=" & std_logic'image(Zero);

        -- ====================================================
        -- 14. AND : 0xFF AND 0xAA = 0xAA
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= x"FF";
        B <= x"AA";
        Cand <= '1';
        wait for T;
        assert S = x"AA"
            report "ECHEC AND FF&AA" severity error;
        report "AND  0xFF & 0xAA = 0x" &
               integer'image(to_integer(unsigned(S)));

        -- ====================================================
        -- 15. OR : 0xF0 OR 0x0F = 0xFF
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= x"F0";
        B <= x"0F";
        Cor <= '1';
        wait for T;
        assert S = x"FF"
            report "ECHEC OR F0|0F" severity error;
        report "OR   0xF0 | 0x0F = 0x" &
               integer'image(to_integer(unsigned(S)));

        -- ====================================================
        -- 16. OR : résultat zéro  0x00 OR 0x00 = 0x00 → Zero
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= x"00";
        B <= x"00";
        Cor <= '1';
        wait for T;
        assert Zero = '1'
            report "ECHEC OR 0|0 : Zero attendu 1" severity error;
        report "OR   0x00 | 0x00 = 0x00  Zero=" & std_logic'image(Zero);

        -- ====================================================
        -- 17. NOT : NOT 0x00 = 0xFF
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= x"00";
        B <= x"00";
        Cnot <= '1';
        wait for T;
        assert S = x"FF"
            report "ECHEC NOT 0x00" severity error;
        report "NOT  0x00 = 0x" &
               integer'image(to_integer(unsigned(S)));

        -- ====================================================
        -- 18. NOT : NOT 0xFF = 0x00 → Zero
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= x"FF";
        B <= x"00";
        Cnot <= '1';
        wait for T;
        assert S = x"00"
            report "ECHEC NOT 0xFF" severity error;
        assert Zero = '1'
            report "ECHEC NOT 0xFF : Zero attendu 1" severity error;
        report "NOT  0xFF = 0x00  Zero=" & std_logic'image(Zero);

        -- ====================================================
        -- 19. NOT : NOT 0xAA = 0x55
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= x"AA";
        Cnot <= '1';
        wait for T;
        assert S = x"55"
            report "ECHEC NOT 0xAA" severity error;
        report "NOT  0xAA = 0x" &
               integer'image(to_integer(unsigned(S)));

        -- ====================================================
        -- 20. Aucune commande active → S = 0x00, Zero = 1
        -- ====================================================
        reset_cmds(Cadd,Csub,Cmul,Cdiv,Cxor,Cand,Cor,Cnot);
        A <= x"AB";
        B <= x"CD";
        wait for T;
        assert S = x"00"
            report "ECHEC IDLE : S attendu 0x00" severity error;
        report "IDLE (aucune commande) S=0x" &
               integer'image(to_integer(unsigned(S)));

        report "========== FIN DES TESTS ALU ==========";
        wait; -- fin de simulation
    end process;

end Behavioral;