import java.sql.*;

import java.util.*;

public class DBSupermercadoConnection {

	String driver;

	String dbName = "SupermercadoV2";

	Properties props = new Properties(); // connection properties
	// providing a user name and password is optional in the embedded
	// and derbyclient frameworks

	String connectionURL = "jdbc:derby:" + dbName + ";create=true";

	public DBSupermercadoConnection(String driver) {
		this.driver = driver;
	}

	public Connection getSupermercadoConnection() {
		Connection conn = null;
		props.put("user", "App");
		props.put("password", "");

		// JDBC code sections
		// Beginning of Primary DB access section
		// ## BOOT DATABASE SECTION ##
		try {
			Class.forName(driver).newInstance();
			// Create (if needed) and connect to the database.
			// The driver is loaded automatically.
			conn = DriverManager.getConnection(connectionURL, props);
			System.out.println("Connected to database " + dbName);
			// Beginning of the primary catch block: prints stack trace
		} catch (Throwable e) {
			/*
			 * Catch all exceptions and pass them to the Throwable.printStackTrace method
			 */
			System.out.println(" . . . exception thrown:");
			e.printStackTrace(System.out);
		}
		return conn;
	}

	public Connection getSupermercadoConnection(boolean check) throws SQLException {
		Connection conn = getSupermercadoConnection();
		if (check && conn != null)
			checkConnection(conn);
		return conn;
	}

	public void checkConnection(Connection conTst) throws SQLException {
		try {
			Statement s = conTst.createStatement();
			// não faz nada porque 1 != 3, mas ao menos executa o comando
			s.execute("update Produto set descricao = '1' where 1=3");
		} catch (SQLException sqle) {
			String theError = (sqle).getSQLState();
			// System.out.println(" Utils GOT: " + theError);
			/** If table exists will get - WARNING 02000: No row was found **/
			if (theError.equals("42X05")) {
				System.out.println("Table does not exist");
				throw sqle;
			} else if (theError.equals("42X14") || theError.equals("42821")) {
				System.out.println("Incorrect table definition. Drop tables and reconfigure");
				throw sqle;
			} else {
				System.out.println("Unhandled SQLException");
				throw sqle;
			}
		}
		System.out.println("Checking Connection: ok - table exists");
	}

}
