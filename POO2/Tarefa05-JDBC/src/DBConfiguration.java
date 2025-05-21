import java.sql.*;

public class DBConfiguration {
	public void launch() {
		String driver = "org.apache.derby.jdbc.EmbeddedDriver";
		DBSupermercadoConnection dbConnection = new DBSupermercadoConnection(driver);
        
		Connection conn;
		Statement stmt;
		
		String dropStringL   = "DROP TABLE Livro";
		String dropStringR   = "DROP TABLE Revista";
		String createStringLivro = "CREATE TABLE Livro"
				+ "(ano                  INT NOT NULL,"
				+ " titulo               VARCHAR(40) NOT NULL, "
				+ " autor               VARCHAR(40) NOT NULL,"
				+ " PRIMARY KEY (ano,titulo,autor)) ";
		String createStringRevista = "CREATE TABLE Revista"
				+ "(ano                  INT NOT NULL,"
				+ " titulo               VARCHAR(40) NOT NULL, "
				+ " vol               INT NOT NULL, "
				+ " nro               INT NOT NULL, "
				+ " org               VARCHAR(40) NOT NULL, "
				+ " PRIMARY KEY (nro)) ";

		// JDBC code sections
		// Beginning of Primary DB access section
		// ## BOOT DATABASE SECTION ##
		conn = dbConnection.getSupermercadoConnection();
		if (conn == null) return;
		try {
			// ## INITIAL SQL SECTION ##
			// Create a statement to issue simple commands.
			stmt = conn.createStatement();
			// Call utility method to check if table exists.
			// Create the table if needed

			System.out.println(" . . . . dropping table Produto");
			stmt.execute(dropStringL);
			stmt.execute(dropStringR);
			System.out.println(" . . . . table Produto dropped\n");
			System.out.println(" . . . . creating tables");
			stmt.execute(createStringLivro);
			stmt.execute(createStringRevista);
			System.out.println(" . . . . table Produto created.");

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
}
