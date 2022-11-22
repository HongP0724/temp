import java.sql.*;
import java.util.Scanner;

public class MovieDB {
	public static Connection makeConnection() {
		String url = "jdbc:mysql://localhost:3306/movie_DB?characterEncoding=UTF-8&serverTimezone=UTC";
		String id = "root";
		String password = "0000";
		Connection con = null;
		try {
			Class.forName("com.mysql.cj.jdbc.Driver");
			System.out.println("드라이버 적재 성공");
			con = DriverManager.getConnection(url, id, password);
			System.out.println("데이터베이스 연결 성공");
		} catch (ClassNotFoundException e) {
			System.out.println("드라이버를 찾을 수 없습니다.");
		} catch (SQLException e) {
			System.out.println("연결에 실패하였습니다.");
		}
		return con;
	}
	
	private static void addMovie(String title, String genre, int year) throws SQLException {
		Connection con = makeConnection();
		try {
	        Statement stmt = con.createStatement();
			String s = "INSERT INTO movies (title, genre, year) VALUES ";
			s += "('" + title + "','" + genre + "','" + year + "')";
			System.out.println(s);
			int i = stmt.executeUpdate(s);
			if (i == 1)
				System.out.println("레코드 추가 성공");
			else
				System.out.println("레코드 추가 실패");
			
			
			con.close();
			
			
		} catch (SQLException e) {
			System.out.println(e.getMessage());
			System.exit(0);
		}
		

         
	}
	
	private static void deleteMovie(int id) throws SQLException {
		Connection con = makeConnection();
		try {
	        Statement stmt = con.createStatement();    
			String s = "delete FROM movies where id = " + id;
			System.out.println(s);
			int i = stmt.executeUpdate(s);
			if (i == 1)
				System.out.println("레코드 삭제 성공");
			else
				System.out.println("레코드 삭제 실패");
			

	        con.close();
		} catch (SQLException e) {
			System.out.println(e.getMessage());
			System.exit(0);
		}
         
	}
	
	private static void showMovies() throws SQLException {
        Connection con = makeConnection();
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM movies");
        while (rs.next()) {
               int id = rs.getInt("id");
               String title = rs.getString("title");
               String genre = rs.getString("genre");
               int year = rs.getInt("year");
               System.out.println(id + " " + title + " " + genre + " " + year);
        }
       con.close();
    }
	
	public static void main(String arg[]) throws SQLException {
		Scanner sc = new Scanner(System.in);
		int input;
		while(true) {
			System.out.println("(1) Movies 테이블의 모든 내용 출력 기능");
			System.out.println("(2) 새로운 영화 정보 레코드 추가 기능");
			System.out.println("(3) id 값을 입력 받아  Movies 테이블에서 삭제 기능");
			System.out.println("(4) 프로그램 종료");
			
			input = sc.nextInt();
			if(input == 1) {
				showMovies();
				System.out.println();
			}
			else if(input == 2) {
				System.out.print("title, genre, year :");
				addMovie(sc.next(),sc.next(),sc.nextInt());
			}
			else if(input == 3) {
				System.out.print("id :");
				deleteMovie(sc.nextInt());
			}
			else if(input == 4) {
				return;
			}
		}
	}
	
	
	
}
