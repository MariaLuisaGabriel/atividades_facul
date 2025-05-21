import java.sql.*;
import java.util.ArrayList;


public class DBPopulation {
	public void launchlivro(ArrayList<Bibliografia> L) {
		System.out.println("lauch population");
		String driver = "org.apache.derby.jdbc.EmbeddedDriver";
		DBSupermercadoConnection dbConnection = new DBSupermercadoConnection(driver);

		Connection conn = null;
		Statement stmt;
		PreparedStatement psInsertL;

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

			// Prepare the insert statement to use
			psInsertL = conn.prepareStatement("insert into "
					+ "Livro(ano, titulo, autor) " + "values (?, ?, ?)");


			// Insert the text entered into the WISH_ITEM table

			for(int i = 0; i<L.size(); i++){
				if(L.get(i) instanceof Livro) {
					psInsertL.setInt(1, L.get(i).getAno());
					psInsertL.setString(2, L.get(i).getTitulo());
					psInsertL.setString(3, ((Livro) L.get(i)).getAutor());
					psInsertL.executeUpdate();
				}
			}

			// Release the resources (clean up )
			psInsertL.close();
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
	public void launchrevista(ArrayList<Bibliografia> L) {
		System.out.println("lauch population");
		String driver = "org.apache.derby.jdbc.EmbeddedDriver";
		DBSupermercadoConnection dbConnection = new DBSupermercadoConnection(driver);

		Connection conn = null;
		Statement stmt;
		PreparedStatement psInsertR;

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

			// Prepare the insert statement to use

			psInsertR = conn.prepareStatement("insert into "
					+ "Revista(titulo, ano, vol, nro, org) " + "values (?, ?, ?, ?, ?)");

			// Insert the text entered into the WISH_ITEM table

			for(int i = 0; i<L.size(); i++){
				if(L.get(i) instanceof Revista) {
					psInsertR.setString(1,L.get(i).getTitulo());
					psInsertR.setInt(2, L.get(i).getAno());
					psInsertR.setInt(3, ((Revista) L.get(i)).getVol());
					psInsertR.setInt(4, ((Revista) L.get(i)).getNumero());
					psInsertR.setString(5,((Revista) L.get(i)).getOrg());
					psInsertR.executeUpdate();
				}
			}

			// Release the resources (clean up )
			psInsertR.close();
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

	/*** Check for WISH_LIST table ****/

}
