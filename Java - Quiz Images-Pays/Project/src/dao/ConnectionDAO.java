package dao;

import java.sql.Connection; //

public class ConnectionDAO
{
	// La classe qui est supposee etre un singleton
	// Pour l'instant la BD est mise de cote
	private static Connection connection = null;
	
	private ConnectionDAO()
	{
		//
	}
	
	static Connection getConnection()
	{
		if (connection == null)
		{
			// connection = ;
		}
		return connection;
	}
	
	static void releaseConnection()
	{
		// connection.close()?
		// connection = null;
	}
	
	static boolean testConnection()
	{
		if (connection == null)
		{
			return false;
		}
		return true;
	}
	
}