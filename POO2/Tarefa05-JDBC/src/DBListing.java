import org.apache.derby.impl.jdbc.EmbedResultSet;
import java.sql.*;
import java.util.ArrayList;

public class DBListing {
	public void launchrevista(ArrayList<Bibliografia> L) {
		System.out.println("lauch revista");
		String driver = "org.apache.derby.jdbc.EmbeddedDriver";
		DBSupermercadoConnection dbConnection = new DBSupermercadoConnection(driver);

		Connection conn = null;
		Statement stmt;
		ResultSet revista;

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
			// Call utility method to check if table exists.
			// Create the table if needed

			// Seleciona todas as linhas em produtos
			revista = stmt.executeQuery(
					"select * from Revista");

			// Loop through the ResultSet and print the data
			System.out.println(printLine);

			while (revista.next()) {
				L.add(new Revista(revista.getString("titulo"),revista.getString("org"),revista.getInt("vol"),revista.getInt("nro"),revista.getInt("ano")));
			}
			System.out.println(printLine);

			// Close the resultSet
			revista.close();

			// Release the resources (clean up )
			stmt.close();
			conn.close();
			System.out.println("Closed connection");

			// Beginning of the primary catch block: prints stack trace
		} catch (Throwable e) {
			/*
			 * Catch all exceptions and pass them to the Throwable.printStackTrace method
			 */
			System.out.println(" . . . exception thrown:");
			e.printStackTrace(System.out);
		}
	}
	public void launchlivro(ArrayList<Bibliografia> L) {
		System.out.println("lauch livro");
		String driver = "org.apache.derby.jdbc.EmbeddedDriver";
		DBSupermercadoConnection dbConnection = new DBSupermercadoConnection(driver);

		Connection conn = null;
		Statement stmt;
		ResultSet livro;

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
			// Call utility method to check if table exists.
			// Create the table if needed

			// Seleciona todas as linhas em produtos
			livro = stmt.executeQuery(
					"select * from Livro");

			// Loop through the ResultSet and print the data
			System.out.println(printLine);
			while (livro.next()) {
				L.add(new Livro(livro.getString("titulo"),livro.getString("autor"),livro.getInt("ano")));
			}
			System.out.println(printLine);

			// Close the resultSet
			livro.close();

			// Release the resources (clean up )
			stmt.close();
			conn.close();
			System.out.println("Closed connection");

			// Beginning of the primary catch block: prints stack trace
		} catch (Throwable e) {
			/*
			 * Catch all exceptions and pass them to the Throwable.printStackTrace method
			 */
			System.out.println(" . . . exception thrown:");
			e.printStackTrace(System.out);
		}
	}

	public boolean checkConnection(Connection conTst) throws SQLException {
		try {
			Statement s = conTst.createStatement();
			// não faz nada porque 1 != 3, mas ao menos executa o comando
			s.execute("update Produto set descricao = '1' where 1=3");
		} catch (SQLException sqle) {
			String theError = (sqle).getSQLState();
			// System.out.println(" Utils GOT: " + theError);
			/** If table exists will get - WARNING 02000: No row was found **/
			if (theError.equals("42X05")) // Table does not exist
			{
				return false;
			} else if (theError.equals("42X14") || theError.equals("42821")) {
				System.out.println("Incorrect table definition. Drop table WISH_LIST and rerun this program");
				throw sqle;
			} else {
				System.out.println("Unhandled SQLException");
				throw sqle;
			}
		}
		System.out.println("Checking Connection: ok - table exists");
		return true;
	}

	/** END getWishItem ***/

	/*** Check for WISH_LIST table ****/

}
