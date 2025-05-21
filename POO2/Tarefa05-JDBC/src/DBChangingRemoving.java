
import java.sql.*;


public class DBChangingRemoving {

	public static void main(String[] args) {
		new DBChangingRemoving().launch();
	}

	public void launch() {
		String driver = "org.apache.derby.jdbc.EmbeddedDriver";
		DBSupermercadoConnection dbConnection = new DBSupermercadoConnection(driver);

		Connection conn = null;
		Statement stmt;
		PreparedStatement psUpdateRemove;

		String printLine = "  __________________________________________________";


		// JDBC code sections
		// Beginning of Primary DB access section
		// ## BOOT DATABASE SECTION ##
		try {
			conn = dbConnection.getSupermercadoConnection();
			if (conn == null)
				return;

			// ## INITIAL SQL SECTION ##
			// Create a statement to issue simple commands.
			stmt = conn.createStatement();

			listaProdutos(stmt, "Antes da atualizacao", printLine);

			// Prepare the insert statement to use
			psUpdateRemove = conn.prepareStatement("update Produto "
					+ "set descricao = 'Novo Chinelo de Dedo' , precoBrutoVendaUnitario = 50.0, estoque = 20.0 where codigo = 1");

			psUpdateRemove.executeUpdate();

			listaProdutos(stmt, " Depois de Atualizar Chinelo ", printLine);
			
			// Prepare the insert statement to use
			psUpdateRemove = conn.prepareStatement("update Produto "
					+ "set descricao = ? , precoBrutoVendaUnitario = ?, estoque = ? where codigo = ?");

			psUpdateRemove.setString(1, "Nova Pantufa");
			psUpdateRemove.setDouble(2, 60.0);
			psUpdateRemove.setDouble(3, 10);
			psUpdateRemove.setInt(4, 2);

			psUpdateRemove.executeUpdate();
			
			listaProdutos(stmt, " Depois de Atualizar Pantufa, antes de remover Chinelo", printLine);

			// Prepare the insert statement to use
			psUpdateRemove = conn.prepareStatement("DELETE FROM Produto where codigo = ?");
 
			psUpdateRemove.setInt(1,1);
			
			psUpdateRemove.executeUpdate();
			
			listaProdutos(stmt, " Depois de remover Chinelo", printLine);

			// Release the resources (clean up )
			psUpdateRemove.close();
			stmt.close();
			conn.close();
			System.out.println("Closed connection");

			// ## DATABASE SHUTDOWN SECTION ##
			/***
			 * In embedded mode, an application should shut down Derby. Shutdown throws the
			 * XJ015 exception to confirm success.
			 ***/
			if (driver.equals("org.apache.derby.jdbc.EmbeddedDriver")) {
				boolean gotSQLExc = false;
				try {
					DriverManager.getConnection("jdbc:derby:;shutdown=true");
				} catch (SQLException se) {
					if (se.getSQLState().equals("XJ015")) {
						gotSQLExc = true;
					}
				}
				if (!gotSQLExc) {
					System.out.println("Database did not shut down normally");
				} else {
					System.out.println("Database shut down normally");
				}
			}

			// Beginning of the primary catch block: prints stack trace
		} catch (Throwable e) {
			/*
			 * Catch all exceptions and pass them to the Throwable.printStackTrace method
			 */
			System.out.println(" . . . exception thrown:");
			e.printStackTrace(System.out);
		}
	}

	private void listaProdutos(Statement stmt, String msg, String printLine) throws SQLException {
		ResultSet produtos;
		// Seleciona todas as linhas em produtos
		produtos = stmt.executeQuery(
				"select codigo, descricao, precoBrutoVendaUnitario, estoque from Produto order by descricao");

		// Loop through the ResultSet and print the data
		System.out.println("__________________ " + msg + " ____________________");
		while (produtos.next()) {
			System.out.println("Cod: " + produtos.getInt(1) + ", Desc: " + produtos.getString(2) + ", Preco: "
					+ produtos.getDouble(3) + ", Estoque: " + produtos.getDouble(4));
		}
		System.out.println(printLine);
		// Close the resultSet
		produtos.close();
	}
}
